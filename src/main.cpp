#include "main.hpp"
#include <iomanip>
#include <sstream>
#include <map>
#include "questui/shared/QuestUI.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"
#include "GlobalNamespace/LevelCompletionResults.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/GamePause.hpp"
#include "GlobalNamespace/BeatmapObjectManager.hpp"
#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/NoteCutInfo.hpp"
#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/ISaberSwingRatingCounter.hpp"
#include "GlobalNameSpace/ScoreModel.hpp"
#include "GlobalNamespace/PlayerSpecificSettings.hpp"
#include "GlobalNamespace/NoteCutDirection.hpp"
#include "GlobalNamespace/CutScoreBuffer.hpp"
#include "GlobalNamespace/ColorScheme.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/MultiplayerResultsViewController.hpp"
#include "Globalnamespace/GameServerLobbyFlowCoordinator.hpp"
#include "Globalnamespace/StandardLevelDetailView.hpp"
#include "GlobalNamespace/LevelCompletionResults.hpp"
#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"

using namespace UnityEngine;
using namespace GlobalNamespace;
using namespace SliceDetails;

SliceDetailsUI* Main::SliceDetailsUI = nullptr;
Config Main::config;
std::map<ISaberSwingRatingCounter*, NoteInfo*> dict;
static auto skillIssue = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("Skill Issue");

static ModInfo modInfo;

Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;

    getConfig().Load();
    getLogger().info("Completed setup!");
}

void Main::loadConfig() {
    getConfig().Load();
    ConfigHelper::LoadConfig(config, getConfig().config);
}

MAKE_HOOK_MATCH(Pause, &GamePause::Pause, void, GamePause* self) {
    Pause(self);
    Main::SliceDetailsUI->onPause();
}

MAKE_HOOK_MATCH(Unpause, &GamePause::Resume, void, GlobalNamespace::GamePause* self) {
    Unpause(self);
    Main::SliceDetailsUI->onUnPause();
}

MAKE_HOOK_MATCH(Menubutton, &PauseMenuManager::MenuButtonPressed , void, PauseMenuManager* self) {
    Menubutton(self);
    Main::SliceDetailsUI->onUnPause();
}

MAKE_HOOK_MATCH(Restartbutton, &PauseMenuManager::RestartButtonPressed, void, PauseMenuManager* self) {
    Restartbutton(self);
    Main::SliceDetailsUI->onUnPause();
}

MAKE_HOOK_MATCH(Results, &ResultsViewController::Init, void, ResultsViewController* self, LevelCompletionResults* levelCompletionResults, IDifficultyBeatmap* difficultyBeatmap, bool practice, bool newHighScore) {
    Results(self, levelCompletionResults, difficultyBeatmap, practice, newHighScore);
    Main::SliceDetailsUI->onResultsScreenActivate();
}

MAKE_HOOK_MATCH(Unresults, &ResultsViewController::DidDeactivate, void, ResultsViewController* self, bool removedFromHierarchy, bool screenSystemDisabling) {
    Unresults(self, removedFromHierarchy, screenSystemDisabling);
    Main::SliceDetailsUI->onResultsScreenDeactivate();
}

MAKE_HOOK_MATCH(MultiResults, &MultiplayerResultsViewController::DidActivate, void, MultiplayerResultsViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    MultiResults(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    Main::SliceDetailsUI->onResultsScreenActivate();
}

MAKE_HOOK_MATCH(BackToLobbyButtonPressed, &MultiplayerResultsViewController::BackToLobbyPressed, void, MultiplayerResultsViewController* self) {
    BackToLobbyButtonPressed(self);
    Main::SliceDetailsUI->onResultsScreenDeactivate();
}

MAKE_HOOK_MATCH(BackToMenuButtonPressed, &MultiplayerResultsViewController::BackToMenuPressed, void, MultiplayerResultsViewController* self) {
    BackToMenuButtonPressed(self);
    Main::SliceDetailsUI->onResultsScreenDeactivate();
}

MAKE_HOOK_MATCH(UnMultiplayer, &GameServerLobbyFlowCoordinator::DidDeactivate, void, GameServerLobbyFlowCoordinator* self, bool removedFromHierarchy, bool screenSystemDisabling){
    UnMultiplayer(self, removedFromHierarchy, screenSystemDisabling);
    if (Main::SliceDetailsUI != nullptr) Main::SliceDetailsUI->onResultsScreenDeactivate();
}

MAKE_HOOK_MATCH(OnNoteCut, &BeatmapObjectManager::HandleNoteControllerNoteWasCut , void, BeatmapObjectManager* self, NoteController* noteController, ByRef<NoteCutInfo> noteCutInfo) {
    OnNoteCut(self, noteController, noteCutInfo);
    if (noteController->noteData->colorType == ColorType::None || !noteCutInfo.heldRef.get_allIsOK()) return;
    if (noteController == nullptr) return;
			
    Vector2 noteGridPosition;
    noteGridPosition.y = (int)noteController->noteData->noteLineLayer;
    noteGridPosition.x = noteController->noteData->lineIndex;
    int noteIndex = (int)((2 - noteGridPosition.y) * 4 + noteGridPosition.x);

    // No ME notes allowed >:(
    if (noteGridPosition.x >= 4 || noteGridPosition.y >= 3 || noteGridPosition.x < 0 || noteGridPosition.y < 0) return;

    float cutAngle = noteCutInfo.heldRef.cutDirDeviation;
    float cutOffset = noteCutInfo.heldRef.cutDistanceToCenter;
    Vector3 noteCenter = noteController->noteTransform->get_position();
    if (UnityEngine::Vector3::Dot(noteCutInfo.heldRef.cutNormal, noteCutInfo.heldRef.cutPoint - noteCenter) > 0.0f)
    {
        cutOffset = -cutOffset;
    }

    // need to add stuff here to put values into array
    int notePosIndex;
    switch (noteController->noteData->cutDirection.value){
        case NoteCutDirection::UpLeft:
            notePosIndex = 0; break;
        case NoteCutDirection::Up:
            notePosIndex = 1; break;
        case NoteCutDirection::UpRight:
            notePosIndex = 2; break;
        case NoteCutDirection::Left:
            notePosIndex = 3; break;
        case NoteCutDirection::Any:
            notePosIndex = 4; break;
        case NoteCutDirection::Right:
            notePosIndex = 5; break;
        case NoteCutDirection::DownLeft:
            notePosIndex = 6; break;
        case NoteCutDirection::Down:
            notePosIndex = 7; break;
        case NoteCutDirection::DownRight:
            notePosIndex = 8; break;
        case NoteCutDirection::None:
            notePosIndex = -1; break;
    }
    if (notePosIndex == -1) return;
    if (noteController->noteData->colorType == ColorType::ColorB){
        notePosIndex += 9;
    }

    NoteInfo* temp = new NoteInfo();
    temp->addNewNoteData(noteIndex, notePosIndex, noteCutInfo.heldRef.cutDistanceToCenter, cutAngle, cutOffset);
    dict.insert(std::make_pair(noteCutInfo.heldRef.swingRatingCounter, temp));
}

// this entire thing might not be necessary. edit: it was very much necessary
MAKE_HOOK_MATCH(HandleSwingFinish, &CutScoreBuffer::HandleSaberSwingRatingCounterDidFinish, void, CutScoreBuffer* self, ISaberSwingRatingCounter* counter) {
    HandleSwingFinish(self, counter);
    // also need to add stuff here
    if (dict.find(counter) != dict.end()){
        NoteInfo* notecutinfo = dict.find(counter)->second;
        int preSwing, postSwing, offset;
        GlobalNamespace::ScoreModel::RawScoreWithoutMultiplier(counter, notecutinfo->offset, preSwing, postSwing, offset);
        Main::SliceDetailsUI->gridNotes[(int)notecutinfo->preswing]->notes[(int)notecutinfo->postswing]->addNewNoteData(preSwing, postSwing, offset, notecutinfo->cutAngle, notecutinfo->cutOffset);
        Main::SliceDetailsUI->gridNotes[(int)notecutinfo->preswing]->addNewGridPosData(preSwing, postSwing, offset);
        dict.erase(counter);
        delete notecutinfo;
    }
}

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(GameplayCoreSceneSetupData_ctor, "", "GameplayCoreSceneSetupData", ".ctor", void, GameplayCoreSceneSetupData* self, IDifficultyBeatmap* difficultyBeatmap, IPreviewBeatmapLevel* previewBeatmapLevel, GameplayModifiers* gameplayModifiers, PlayerSpecificSettings* playerSpecificSettings, PracticeSettings* practiceSettings, bool useTestNoteCutSoundEffects, EnvironmentInfoSO* environmentInfo, ColorScheme* colorScheme)
{
    //colorScheme valid here ^_^
    GameplayCoreSceneSetupData_ctor(self, difficultyBeatmap, previewBeatmapLevel, gameplayModifiers, playerSpecificSettings, practiceSettings, useTestNoteCutSoundEffects, environmentInfo, colorScheme);

    bool firstActivation = false;
    if (Main::SliceDetailsUI == nullptr){
        firstActivation = true;
        Main::SliceDetailsUI = (SliceDetailsUI*)malloc(sizeof(SliceDetailsUI));
        Main::SliceDetailsUI->initScreen();
    }
    Main::SliceDetailsUI->UIScreen->set_active(false);

    if (firstActivation) Main::SliceDetailsUI->initNoteData();
    else Main::SliceDetailsUI->refreshNoteData();
    Main::SliceDetailsUI->leftHand = colorScheme->get_saberAColor();
    Main::SliceDetailsUI->rightHand = colorScheme->get_saberBColor();
}

MAKE_HOOK_MATCH(MenuTransitionsHelper_RestartGame, &MenuTransitionsHelper::RestartGame, void, MenuTransitionsHelper* self, System::Action_1<Zenject::DiContainer*>* finishCallback)
{
    delete Main::SliceDetailsUI;
    Main::SliceDetailsUI = nullptr;
    MenuTransitionsHelper_RestartGame(self, finishCallback);
}

//ha ha funny skilly issue
MAKE_HOOK_MATCH(levelview, &StandardLevelDetailView::RefreshContent, void, StandardLevelDetailView* self){
    levelview(self);
    self->practiceButton->get_transform()->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->SetText(skillIssue);
}


// Called later on in the game loading - a good time to install function hooks
extern "C" void load() {
    il2cpp_functions::Init();
    Main::loadConfig();
    QuestUI::Init();
    custom_types::Register::AutoRegister();
    getLogger().info("Installing hooks...");
    // Install our hooks
    INSTALL_HOOK(getLogger(), Pause);
    INSTALL_HOOK(getLogger(), Results);
    INSTALL_HOOK(getLogger(), OnNoteCut);
    INSTALL_HOOK(getLogger(), HandleSwingFinish);
    INSTALL_HOOK(getLogger(), GameplayCoreSceneSetupData_ctor);
    INSTALL_HOOK(getLogger(), Unpause);
    INSTALL_HOOK(getLogger(), Menubutton);
    INSTALL_HOOK(getLogger(), Restartbutton);
    INSTALL_HOOK(getLogger(), Unresults);
    INSTALL_HOOK(getLogger(), MultiResults);
    INSTALL_HOOK(getLogger(), BackToLobbyButtonPressed);
    INSTALL_HOOK(getLogger(), BackToMenuButtonPressed);
    INSTALL_HOOK(getLogger(), UnMultiplayer);
    INSTALL_HOOK(getLogger(), MenuTransitionsHelper_RestartGame);
    INSTALL_HOOK(getLogger(), levelview);
    getLogger().info("Installed all hooks!");
}