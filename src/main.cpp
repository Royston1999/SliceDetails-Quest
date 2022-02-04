#include "main.hpp"
#include <iomanip>
#include <sstream>
#include <cmath>
#include <map>
#define _USE_MATH_DEFINES
#include "math.h"
#include "questui/shared/QuestUI.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"
#include "System/Math.hpp"
#include "HMUI/ImageView.hpp"
#include "GlobalNamespace/ScoreFormatter.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/RectOffset.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/TextAnchor.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Space.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "GlobalNamespace/LevelCompletionResults.hpp"
#include "GlobalNamespace/PauseMenuManager.hpp"
#include "GlobalNamespace/GamePause.hpp"
#include "UI/ClickableImage.hpp"
#include "UI/HoverClickHelper.hpp"
#include "UI/NoteUI.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/Screen.hpp"
#include "HMUI/HoverHintPanel.hpp"
#include "questui/shared/CustomTypes/Components/FloatingScreen/FloatingScreenManager.hpp"
#include "GlobalNamespace/ComboUIController.hpp"
#include "GlobalNamespace/VRControllersInputManager.hpp"
#include "UnityEngine/UI/VerticalLayoutGroup.hpp"
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "UnityEngine/UI/CanvasScaler.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "Resources/Sprites.hpp"
#include "questui/shared/CustomTypes/Components/FloatingScreen/FloatingScreenMoverPointer.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "UnityEngine/BoxCollider.hpp"
#include "UI/ModalHelper.hpp"
#include "Data/GridInfo.hpp"
#include "Data/NoteInfo.hpp"
#include "GlobalNamespace/BeatmapObjectManager.hpp"
#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/NoteCutInfo.hpp"
#include "GlobalNamespace/BeatmapObjectExecutionRatingsRecorder_CutScoreHandler.hpp"
#include "GlobalNamespace/NoteData.hpp"
#include "GlobalNamespace/ISaberSwingRatingCounter.hpp"
#include "GlobalNameSpace/ScoreModel.hpp"
#include "GlobalNamespace/StandardLevelDetailViewController.hpp"
#include "GlobalNamespace/PracticeViewController.hpp"
#include "GlobalNamespace/StandardLevelDetailView.hpp"
#include "GlobalNamespace/PlatformLeaderboardViewController.hpp"
#include "GlobalNamespace/PlayerLevelStatsData.hpp"
#include "GlobalNamespace/MenuTransitionsHelper.hpp"
#include "GlobalNamespace/OverrideEnvironmentSettings.hpp"
#include "GlobalNamespace/PlayerSpecificSettings.hpp"
#include "GlobalNamespace/NoteCutDirection.hpp"
#include "GlobalNamespace/ISaberSwingRatingCounterDidFinishReceiver.hpp"
#include "GlobalNamespace/CutScoreBuffer.hpp"
#include "GlobalNamespace/ColorScheme.hpp"
#include "GlobalNamespace/ColorSchemeSO.hpp"
#include "GlobalNamespace/EnvironmentColorManager.hpp"
#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"
#include "GlobalNamespace/MultiplayerResultsViewController.hpp"
#include "Globalnamespace/GameServerLobbyFlowCoordinator.hpp"
#include "Globalnamespace/StandardLevelDetailView.hpp"
#include "GlobalNamespace/LevelCompletionResults.hpp"
#include "GlobalNamespace/IDifficultyBeatmap.hpp"
#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "VRUIControls/VRLaserPointer.hpp"


using namespace UnityEngine;
using namespace GlobalNamespace;
using namespace SliceDetails;

SliceDetails::SliceDetailsUI* Main::SliceDetailsUI = nullptr;
Config Main::config;
GlobalNamespace::VRController* SliceDetails::HoverClickHelper::grabbingController = nullptr;
bool SliceDetails::HoverClickHelper::triggerPressed = false;
std::map<ISaberSwingRatingCounter*, NoteInfo*> dict;
bool Main::isPaused = false;
static auto skillIssue = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("Skill Issue");
UnityEngine::Material* Main::UINoGlow = nullptr;


static ModInfo modInfo; // Stores the ID and version of our mod, and is sent to the modloader upon startup

// Loads the config from disk using our modInfo, then returns it for use
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

// Returns a logger, useful for printing debug messages
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = ID;
    info.version = VERSION;
    modInfo = info;

    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

void Main::loadConfig() {
    getConfig().Load();
    ConfigHelper::LoadConfig(config, getConfig().config);
}

void onResultsScreenActivate(){
    Main::SliceDetailsUI->updatePanelImages();
    Main::SliceDetailsUI->UIScreen->get_transform()->set_position(UnityEngine::Vector3(SliceDetails::Main::config.resultPosX , SliceDetails::Main::config.resultPosY, SliceDetails::Main::config.resultPosZ));
    Main::SliceDetailsUI->UIScreen->get_transform()->set_rotation(UnityEngine::Quaternion::Euler(SliceDetails::Main::config.resultRotX, SliceDetails::Main::config.resultRotY, SliceDetails::Main::config.resultRotZ));
    Main::SliceDetailsUI->UIScreen->set_active(true);
    Main::SliceDetailsUI->modal->Show(false, true, nullptr);
    Main::SliceDetailsUI->modal->Hide(false, nullptr);
}

void onResultsScreenDeactivate(){
    if (Main::SliceDetailsUI->UIScreen != nullptr){
        Main::SliceDetailsUI->modal->Hide(false, nullptr);
        Main::SliceDetailsUI->UIScreen->set_active(false);
    }
}

void onUnPause(){
    Main::isPaused = false;
    Main::SliceDetailsUI->UIScreen->set_active(false);
}

MAKE_HOOK_MATCH(Pause, &GlobalNamespace::GamePause::Pause, void, GlobalNamespace::GamePause* self) {
    Pause(self);
    // do some big brain shit here idk
    Main::isPaused = true;
    Main::SliceDetailsUI->UIScreen->get_transform()->set_position(UnityEngine::Vector3(SliceDetails::Main::config.pausePosX, SliceDetails::Main::config.pausePosY, SliceDetails::Main::config.pausePosZ));
    Main::SliceDetailsUI->UIScreen->get_transform()->set_rotation(UnityEngine::Quaternion::Euler(SliceDetails::Main::config.pauseRotX, SliceDetails::Main::config.pauseRotY, SliceDetails::Main::config.pauseRotZ));
    Main::SliceDetailsUI->UIScreen->set_active(true);
    Main::SliceDetailsUI->modal->Show(false, true, nullptr);
    Main::SliceDetailsUI->modal->Hide(false, nullptr);
    
    auto* pausepointer = Resources::FindObjectsOfTypeAll<VRUIControls::VRPointer*>()->get(1);
    auto* mover = pausepointer->get_gameObject()->AddComponent<QuestUI::FloatingScreenMoverPointer*>();
    mover->Init(Main::SliceDetailsUI->UIScreen->GetComponent<QuestUI::FloatingScreen*>(), pausepointer);
    SliceDetails::addHoverClickHelper(pausepointer, Main::SliceDetailsUI->screenhandle);
    SliceDetails::addModalHelper(pausepointer);
    Main::SliceDetailsUI->updatePanelImages();
}

MAKE_HOOK_MATCH(Unpause, &GlobalNamespace::GamePause::Resume, void, GlobalNamespace::GamePause* self) {
    Unpause(self);
    onUnPause();
}

MAKE_HOOK_MATCH(Menubutton, &GlobalNamespace::PauseMenuManager::MenuButtonPressed , void, GlobalNamespace::PauseMenuManager* self) {
    Menubutton(self);
    onUnPause();
}

MAKE_HOOK_MATCH(Restartbutton, &GlobalNamespace::PauseMenuManager::RestartButtonPressed, void, GlobalNamespace::PauseMenuManager* self) {
    Restartbutton(self);
    onUnPause();
}

MAKE_HOOK_MATCH(Results, &ResultsViewController::Init, void, ResultsViewController* self, GlobalNamespace::LevelCompletionResults* levelCompletionResults, GlobalNamespace::IDifficultyBeatmap* difficultyBeatmap, bool practice, bool newHighScore) {
    Results(self, levelCompletionResults, difficultyBeatmap, practice, newHighScore);
    onResultsScreenActivate();
}

MAKE_HOOK_MATCH(Unresults, &ResultsViewController::DidDeactivate, void, ResultsViewController* self, bool removedFromHierarchy, bool screenSystemDisabling) {
    Unresults(self, removedFromHierarchy, screenSystemDisabling);
    onResultsScreenDeactivate();
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
MAKE_HOOK_MATCH(HandleSwingFinish, &GlobalNamespace::CutScoreBuffer::HandleSaberSwingRatingCounterDidFinish, void, GlobalNamespace::CutScoreBuffer* self, ISaberSwingRatingCounter* counter) {
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

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(GameplayCoreSceneSetupData_ctor, "", "GameplayCoreSceneSetupData", ".ctor", void, GlobalNamespace::GameplayCoreSceneSetupData* self, GlobalNamespace::IDifficultyBeatmap* difficultyBeatmap, GlobalNamespace::IPreviewBeatmapLevel* previewBeatmapLevel, GlobalNamespace::GameplayModifiers* gameplayModifiers, GlobalNamespace::PlayerSpecificSettings* playerSpecificSettings, GlobalNamespace::PracticeSettings* practiceSettings, bool useTestNoteCutSoundEffects, GlobalNamespace::EnvironmentInfoSO* environmentInfo, GlobalNamespace::ColorScheme* colorScheme)
{
    //colorScheme valid here ^_^
    GameplayCoreSceneSetupData_ctor(self, difficultyBeatmap, previewBeatmapLevel, gameplayModifiers, playerSpecificSettings, practiceSettings, useTestNoteCutSoundEffects, environmentInfo, colorScheme);

    bool firstActivation = false;
    if (Main::SliceDetailsUI == nullptr){
        firstActivation = true;
        Main::SliceDetailsUI = (SliceDetails::SliceDetailsUI*)malloc(sizeof(SliceDetails::SliceDetailsUI));
        Main::SliceDetailsUI->initScreen();
    }
    Main::SliceDetailsUI->UIScreen->set_active(false);

    if (firstActivation) Main::SliceDetailsUI->initNoteData();
    else Main::SliceDetailsUI->refreshNoteData();
    Main::SliceDetailsUI->leftHand = colorScheme->get_saberAColor();
    Main::SliceDetailsUI->rightHand = colorScheme->get_saberBColor();
}

MAKE_HOOK_MATCH(MultiResults, &MultiplayerResultsViewController::DidActivate, void, MultiplayerResultsViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    MultiResults(self, firstActivation, addedToHierarchy, screenSystemEnabling);
    onResultsScreenActivate();
}

MAKE_HOOK_MATCH(BackToLobbyButtonPressed, &MultiplayerResultsViewController::BackToLobbyPressed, void, MultiplayerResultsViewController* self) {
    BackToLobbyButtonPressed(self);
    onResultsScreenDeactivate();
}

MAKE_HOOK_MATCH(BackToMenuButtonPressed, &MultiplayerResultsViewController::BackToMenuPressed, void, MultiplayerResultsViewController* self) {
    BackToMenuButtonPressed(self);
    onResultsScreenDeactivate();
}

MAKE_HOOK_MATCH(UnMultiplayer, &GameServerLobbyFlowCoordinator::DidDeactivate, void, GameServerLobbyFlowCoordinator* self, bool removedFromHierarchy, bool screenSystemDisabling){
    UnMultiplayer(self, removedFromHierarchy, screenSystemDisabling);
    onResultsScreenDeactivate();
}

MAKE_HOOK_MATCH(MenuTransitionsHelper_RestartGame, &GlobalNamespace::MenuTransitionsHelper::RestartGame, void, GlobalNamespace::MenuTransitionsHelper* self, System::Action_1<Zenject::DiContainer*>* finishCallback)
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
    // QuestUI::Register::RegisterModSettingsFlowCoordinator<SaberTailor::SettingsFlowCoordinator*>(modInfo);
    getLogger().info("Installing hooks...");
    // Install our hooks (none defined yet)
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