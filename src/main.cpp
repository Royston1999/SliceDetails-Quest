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

Config Main::config;
UnityEngine::GameObject* testScreen = nullptr;
HMUI::ModalView* Main::modal = nullptr;
GlobalNamespace::VRController* SliceDetails::HoverClickHelper::grabbingController = nullptr;
bool SliceDetails::HoverClickHelper::triggerPressed = false;
SliceDetails::NoteUI* modalNotes[18];
SliceDetails::GridInfo* Main::gridNotes[12];
UnityEngine::UI::Image* gridDots[12];
SliceDetails::ClickableImage* panelImages[12];
std::map<ISaberSwingRatingCounter*, NoteInfo*> dict;
UnityEngine::Color leftHand;
UnityEngine::Color rightHand;
bool Main::isPaused = false;
static auto skillIssue = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("Skill Issue");
UnityEngine::Material* Main::UINoGlow = nullptr;
UnityEngine::GameObject* screenhandle = nullptr;
custom_types::Helpers::Coroutine createGridDots(UI::HorizontalLayoutGroup* line1, UI::HorizontalLayoutGroup* line2, UI::HorizontalLayoutGroup* line3);
custom_types::Helpers::Coroutine createNotes(UI::HorizontalLayoutGroup* leftLine1, UI::HorizontalLayoutGroup* leftLine2, UI::HorizontalLayoutGroup* leftLine3, UI::HorizontalLayoutGroup* rightLine1, UI::HorizontalLayoutGroup* rightLine2, UI::HorizontalLayoutGroup* rightLine3);
custom_types::Helpers::Coroutine createPanelNotes(UI::HorizontalLayoutGroup* line1, UI::HorizontalLayoutGroup* line2, UI::HorizontalLayoutGroup* line3);

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

void createGridIndicator(UnityEngine::Transform* parent){
    auto* screen = QuestUI::BeatSaberUI::CreateFloatingScreen({300.0f, 200.0f}, {0.0f, 1.0f, 1.0f}, {0, 0, 0}, 0.0f, true, false, 0);
    screen->GetComponent<QuestUI::FloatingScreen*>()->bgGo->GetComponentInChildren<QuestUI::Backgroundable*>()->ApplyBackgroundWithAlpha(il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("round-rect-panel"), 0.985f);
    auto* vert = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(screen->get_transform());
    auto* line1 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(vert->get_transform());
    auto* line2 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(vert->get_transform());
    auto* line3 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(vert->get_transform());

    line1->set_spacing(60.8f); line2->set_spacing(60.8f); line3->set_spacing(60.8f); vert->set_spacing(-5.5f);

    GlobalNamespace::SharedCoroutineStarter::get_instance()->StartCoroutine(reinterpret_cast<custom_types::Helpers::enumeratorT*>(custom_types::Helpers::CoroutineHelper::New(createGridDots(line1, line2, line3))));

    screen->get_transform()->set_position(screen->get_transform()->get_localPosition() + Vector3(0.0f, 15.0f, -1.2f));
    screen->get_transform()->SetParent(parent, false);
}

custom_types::Helpers::Coroutine createGridDots(UI::HorizontalLayoutGroup* line1, UI::HorizontalLayoutGroup* line2, UI::HorizontalLayoutGroup* line3)
{
    for (int i=0; i<12; i++){
        auto* layout = i<4 ? line1 : i<8 ? line2 : i<12 ? line3 : nullptr;
        gridDots[i] = QuestUI::BeatSaberUI::CreateImage(layout->get_transform(), QuestUI::BeatSaberUI::Base64ToSprite(SliceDetails::Sprites::dot), {0, 0}, {16, 16});
        gridDots[i]->get_transform()->set_localScale({45.0f, 45.0f, 0.0f});
        co_yield nullptr;
    }
    co_return;
}

void createModalUI(UnityEngine::Transform* parent){
    Main::modal = QuestUI::BeatSaberUI::CreateModal(parent, UnityEngine::Vector2(70, 32), [](HMUI::ModalView *modal) {}, true);
    Main::modal->get_transform()->Translate({0.0f, 0.0f, -0.01f});

    auto* mainLayout = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(Main::modal->get_transform());

    auto* leftSide = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(mainLayout->get_transform());
    auto* rightSide = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(mainLayout->get_transform());

    auto* leftLine1 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(leftSide->get_transform());
    auto* leftLine2 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(leftSide->get_transform());
    auto* leftLine3 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(leftSide->get_transform());

    auto* rightLine1 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(rightSide->get_transform());
    auto* rightLine2 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(rightSide->get_transform());
    auto* rightLine3 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(rightSide->get_transform());

    leftLine1->set_spacing(9.4f); leftLine2->set_spacing(9.4f); leftLine3->set_spacing(9.4f); leftSide->set_spacing(9.4f);

    rightLine1->set_spacing(9.4f); rightLine2->set_spacing(9.4f); rightLine3->set_spacing(9.4f); rightSide->set_spacing(9.4f);

    GlobalNamespace::SharedCoroutineStarter::get_instance()->StartCoroutine(reinterpret_cast<custom_types::Helpers::enumeratorT*>(custom_types::Helpers::CoroutineHelper::New(createNotes(leftLine1, leftLine2, leftLine3, rightLine1, rightLine2, rightLine3))));
}

custom_types::Helpers::Coroutine createNotes(UI::HorizontalLayoutGroup* leftLine1, UI::HorizontalLayoutGroup* leftLine2, UI::HorizontalLayoutGroup* leftLine3, UI::HorizontalLayoutGroup* rightLine1, UI::HorizontalLayoutGroup* rightLine2, UI::HorizontalLayoutGroup* rightLine3)
{
    int rots[9] = {225, 180, 135, 270, 0, 90, 315, 0, 45};
    for (int i=0; i<18; i++){
        auto* layout = i<3 ? leftLine1 : i<6 ? leftLine2 : i<9 ? leftLine3 : i<12 ? rightLine1 : i<15 ? rightLine2 : i<18 ? rightLine3 : nullptr;
        modalNotes[i] = new NoteUI(layout->get_transform(), QuestUI::BeatSaberUI::Base64ToSprite(i%9 == 4 ? Sprites::dot : Sprites::bloq_arrow), rots[i%9]);
        co_yield nullptr;
    }
    co_return;
}

void SliceDetails::Main::updateModalNotes(int index){
    for (int i = 0; i < 18; i++) {
        if (i<12) gridDots[i]->set_color(UnityEngine::Color::get_gray());
        if (gridNotes[index]->notes[i]->cutCount != 0){
            float realOffset = (gridNotes[index]->notes[i]->cutOffset / gridNotes[index]->notes[i]->cutCount) * 23.0f;
            float realAngle = (gridNotes[index]->notes[i]->cutAngle / gridNotes[index]->notes[i]->cutCount) - modalNotes[i]->rot;
            modalNotes[i]->noteCutArrow->get_gameObject()->set_active(true);
            modalNotes[i]->cutDistanceImage->get_gameObject()->set_active(true);
            
            modalNotes[i]->noteCutArrow->get_transform()->set_localRotation(UnityEngine::Quaternion::Euler({0.0f, 0.0f, realAngle}));
            modalNotes[i]->noteCutArrow->get_transform()->set_localPosition({realOffset * (float)std::cos(realAngle * M_PI / 180), realOffset * (float)std::sin(realAngle * M_PI / 180), 0.0f});
            modalNotes[i]->cutDistanceImage->get_transform()->set_localRotation(UnityEngine::Quaternion::Euler({0.0f, 0.0f, realAngle}));
            modalNotes[i]->cutDistanceImage->get_transform()->set_localPosition(modalNotes[i]->noteCutArrow->get_transform()->get_localPosition() / 2);
            modalNotes[i]->cutDistanceImage->get_transform()->set_localScale({realOffset / 4.0f, modalNotes[i]->cutDistanceImage->get_transform()->get_localScale().y});
            // modalNotes[i]->cutDistanceImage->set_color(i > 8 ? Color(1.0f-rightHand.r, 1.0f-rightHand.g, 1.0f-rightHand.b, 0.75f) : Color(1.0f-leftHand.r, 1.0f-leftHand.g, 1.0f-leftHand.b, 0.75f));
            modalNotes[i]->noteBackground->set_color(i > 8 ? rightHand : leftHand);
            modalNotes[i]->hint->get_gameObject()->set_active(true);
            modalNotes[i]->hint->set_text(il2cpp_utils::createcsstr(Main::gridNotes[index]->notes[i]->getAverageValueStringData()));
        }
        else{
            modalNotes[i]->cutDistanceImage->get_gameObject()->set_active(false);
            modalNotes[i]->hint->get_gameObject()->set_active(false);
            modalNotes[i]->noteBackground->set_color(UnityEngine::Color::get_gray());
            modalNotes[i]->noteCutArrow->get_gameObject()->set_active(false);
        }
    }
    gridDots[index]->set_color(UnityEngine::Color::get_white());
}

void updatePanelImages(){
    for (int i = 0; i<12; i++){
        panelImages[i]->theHint->set_text(il2cpp_utils::createcsstr(Main::gridNotes[i]->cutCount != 0 ? Main::gridNotes[i]->getAverageValueStringData() : ""));
        panelImages[i]->text->GetComponent<TMPro::TextMeshProUGUI*>()->set_text(il2cpp_utils::createcsstr(Main::gridNotes[i]->cutCount != 0 ?  Main::gridNotes[i]->getAverageScoreString() : ""));
    }
}

void onResultsScreenActivate(){
    updatePanelImages();
    testScreen->get_transform()->set_position(UnityEngine::Vector3(SliceDetails::Main::config.resultPosX , SliceDetails::Main::config.resultPosY, SliceDetails::Main::config.resultPosZ));
    testScreen->get_transform()->set_rotation(UnityEngine::Quaternion::Euler(SliceDetails::Main::config.resultRotX, SliceDetails::Main::config.resultRotY, SliceDetails::Main::config.resultRotZ));
    testScreen->set_active(true);
    Main::modal->Show(false, true, nullptr);
    Main::modal->Hide(false, nullptr);
}

void onResultsScreenDeactivate(){
    if (testScreen != nullptr){
        Main::modal->Hide(false, nullptr);
        testScreen->set_active(false);
    }
}

void onUnPause(){
    Main::isPaused = false;
    testScreen->set_active(false);
}

void initScreen(){
    testScreen = QuestUI::BeatSaberUI::CreateFloatingScreen({40.0f, 32.0f}, {0.0f, 1.0f, 1.0f}, {0, 0, 0}, 0.0f, true, true, 0);
    testScreen->set_active(false);
    testScreen->GetComponent<UnityEngine::Canvas*>()->set_sortingOrder(31);
    UnityEngine::GameObject::DontDestroyOnLoad(testScreen);
    screenhandle = testScreen->GetComponent<QuestUI::FloatingScreen*>()->handle;
    testScreen->GetComponent<QuestUI::FloatingScreen*>()->bgGo->GetComponentInChildren<QuestUI::Backgroundable*>()->ApplyBackgroundWithAlpha(il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("round-rect-panel"), 1.0f);
    screenhandle->get_transform()->set_localPosition(UnityEngine::Vector3(0.0f, -15.0f, 0.0f));
    screenhandle->get_transform()->set_localScale(UnityEngine::Vector3(3.3f, 3.3f, 3.3f));
    QuestUI::FloatingScreen* thing = testScreen->GetComponent<QuestUI::FloatingScreen*>();

    auto* vert = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(testScreen->get_transform());
    auto* line1 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(vert->get_transform());
    auto* line2 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(vert->get_transform());
    auto* line3 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(vert->get_transform());

    line1->set_spacing(8.8f); line2->set_spacing(8.8f); line3->set_spacing(8.8f); vert->set_spacing(-5.5f);

    GlobalNamespace::SharedCoroutineStarter::get_instance()->StartCoroutine(reinterpret_cast<custom_types::Helpers::enumeratorT*>(custom_types::Helpers::CoroutineHelper::New(createPanelNotes(line1, line2, line3))));

    auto* screenthingidk = thing->get_gameObject()->AddComponent<HMUI::Screen*>();
    SliceDetails::Main::UINoGlow = QuestUI::ArrayUtil::First(UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Material*>(), [](UnityEngine::Material* x) { return to_utf8(csstrtostr(x->get_name())) == "UINoGlow"; });
    createModalUI(thing->get_transform());
    createGridIndicator(Main::modal->get_transform());

    auto* normalpointer = Resources::FindObjectsOfTypeAll<VRUIControls::VRPointer*>()->get(0);
    SliceDetails::addHoverClickHelper(normalpointer, screenhandle);
    SliceDetails::addModalHelper(normalpointer);
}

custom_types::Helpers::Coroutine createPanelNotes(UI::HorizontalLayoutGroup* line1, UI::HorizontalLayoutGroup* line2, UI::HorizontalLayoutGroup* line3)
{
    for (int i=0; i<12; i++){
        auto* layout = i<4 ? line1 : i<8 ? line2 : i<12 ? line3 : nullptr;
        panelImages[i] = SliceDetails::CreateClickableImage(layout->get_transform(), "bloq", QuestUI::BeatSaberUI::Base64ToSprite(SliceDetails::Sprites::bloq), "115", i);
        co_yield nullptr;
    }
    co_return;
}

MAKE_HOOK_MATCH(Pause, &GlobalNamespace::GamePause::Pause, void, GlobalNamespace::GamePause* self) {
    Pause(self);
    // do some big brain shit here idk
    Main::isPaused = true;
    testScreen->get_transform()->set_position(UnityEngine::Vector3(SliceDetails::Main::config.pausePosX, SliceDetails::Main::config.pausePosY, SliceDetails::Main::config.pausePosZ));
    testScreen->get_transform()->set_rotation(UnityEngine::Quaternion::Euler(SliceDetails::Main::config.pauseRotX, SliceDetails::Main::config.pauseRotY, SliceDetails::Main::config.pauseRotZ));
    testScreen->set_active(true);
    Main::modal->Show(false, true, nullptr);
    Main::modal->Hide(false, nullptr);
    
    auto* pausepointer = Resources::FindObjectsOfTypeAll<VRUIControls::VRPointer*>()->get(1);
    auto* mover = pausepointer->get_gameObject()->AddComponent<QuestUI::FloatingScreenMoverPointer*>();
    mover->Init(testScreen->GetComponent<QuestUI::FloatingScreen*>(), pausepointer);
    SliceDetails::addHoverClickHelper(pausepointer, screenhandle);
    SliceDetails::addModalHelper(pausepointer);
    updatePanelImages();
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

    Vector3 cutDirection = UnityEngine::Vector3(-noteCutInfo.heldRef.cutNormal.y, noteCutInfo.heldRef.cutNormal.x, 0.0f);
    float cutAngle = std::atan2(cutDirection.y, cutDirection.x) * (180 / M_PI) + 90.0f;

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
    if (noteController->noteData->colorType == ColorType::ColorB) notePosIndex += 9;
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
        Main::gridNotes[(int)notecutinfo->preswing]->notes[(int)notecutinfo->postswing]->addNewNoteData(preSwing, postSwing, offset, notecutinfo->cutAngle, notecutinfo->cutOffset);
        Main::gridNotes[(int)notecutinfo->preswing]->addNewGridPosData(preSwing, postSwing, offset);
        dict.erase(counter);
        delete notecutinfo;
    }
}

MAKE_HOOK_FIND_CLASS_UNSAFE_INSTANCE(GameplayCoreSceneSetupData_ctor, "", "GameplayCoreSceneSetupData", ".ctor", void, GlobalNamespace::GameplayCoreSceneSetupData* self, GlobalNamespace::IDifficultyBeatmap* difficultyBeatmap, GlobalNamespace::IPreviewBeatmapLevel* previewBeatmapLevel, GlobalNamespace::GameplayModifiers* gameplayModifiers, GlobalNamespace::PlayerSpecificSettings* playerSpecificSettings, GlobalNamespace::PracticeSettings* practiceSettings, bool useTestNoteCutSoundEffects, GlobalNamespace::EnvironmentInfoSO* environmentInfo, GlobalNamespace::ColorScheme* colorScheme)
{
    //colorScheme valid here ^_^
    GameplayCoreSceneSetupData_ctor(self, difficultyBeatmap, previewBeatmapLevel, gameplayModifiers, playerSpecificSettings, practiceSettings, useTestNoteCutSoundEffects, environmentInfo, colorScheme);
    leftHand = colorScheme->get_saberAColor();
    rightHand = colorScheme->get_saberBColor();

    if (testScreen == nullptr) initScreen();
    testScreen->set_active(false);

    for (int i = 0; i < 12; i++) {
		delete Main::gridNotes[i];
		Main::gridNotes[i] = new SliceDetails::GridInfo(); 
	}
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
    UnityEngine::GameObject::Destroy(testScreen);
    testScreen = nullptr;
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