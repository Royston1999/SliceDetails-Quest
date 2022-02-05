#include "SliceDetailsUI.hpp"
#include "main.hpp"

using namespace UnityEngine::UI;
using namespace UnityEngine;

namespace SliceDetails{
    void SliceDetailsUI::createGridIndicator(UnityEngine::Transform* parent){
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

    custom_types::Helpers::Coroutine SliceDetailsUI::createGridDots(HorizontalLayoutGroup* line1, HorizontalLayoutGroup* line2, HorizontalLayoutGroup* line3)
    {
        for (int i=0; i<12; i++){
            auto* layout = i<4 ? line1 : i<8 ? line2 : i<12 ? line3 : nullptr;
            gridDots[i] = QuestUI::BeatSaberUI::CreateImage(layout->get_transform(), QuestUI::BeatSaberUI::Base64ToSprite(SliceDetails::Sprites::dot), {0, 0}, {16, 16});
            gridDots[i]->get_transform()->set_localScale({45.0f, 45.0f, 0.0f});
            co_yield nullptr;
        }
        co_return;
    }

    void SliceDetailsUI::createModalUI(UnityEngine::Transform* parent){
        modal = QuestUI::BeatSaberUI::CreateModal(parent, UnityEngine::Vector2(70, 32), [](HMUI::ModalView *modal) {}, true);
        modal->get_transform()->Translate({0.0f, 0.0f, -0.01f});

        auto* mainLayout = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(modal->get_transform());

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

    custom_types::Helpers::Coroutine SliceDetailsUI::createNotes(HorizontalLayoutGroup* leftLine1, HorizontalLayoutGroup* leftLine2, HorizontalLayoutGroup* leftLine3, HorizontalLayoutGroup* rightLine1, HorizontalLayoutGroup* rightLine2, HorizontalLayoutGroup* rightLine3)
    {
        int rots[9] = {225, 180, 135, 270, 0, 90, 315, 0, 45};
        for (int i=0; i<18; i++){
            auto* layout = i<3 ? leftLine1 : i<6 ? leftLine2 : i<9 ? leftLine3 : i<12 ? rightLine1 : i<15 ? rightLine2 : i<18 ? rightLine3 : nullptr;
            modalNotes[i] = new NoteUI(layout->get_transform(), QuestUI::BeatSaberUI::Base64ToSprite(i%9 == 4 ? Sprites::dot : Sprites::bloq_arrow), rots[i%9]);
            co_yield nullptr;
        }
        co_return;
    }

    void SliceDetailsUI::updateGridNotesInfo(int index){
        for (int i = 0; i < 18; i++) {
            if (i<12) gridDots[i]->set_color(UnityEngine::Color::get_gray());
            if (gridNotes[index]->notes[i]->cutCount != 0){
                float realOffset = (gridNotes[index]->notes[i]->cutOffset / gridNotes[index]->notes[i]->cutCount) * 23.0f;
                float realAngle = (gridNotes[index]->notes[i]->cutAngle / gridNotes[index]->notes[i]->cutCount);
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
                modalNotes[i]->hint->set_text(il2cpp_utils::createcsstr(gridNotes[index]->notes[i]->getAverageValueStringData()));
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

    void SliceDetailsUI::updatePanelImages(){
        for (int i = 0; i<12; i++){
            panelImages[i]->theHint->set_text(il2cpp_utils::createcsstr(gridNotes[i]->cutCount != 0 ? gridNotes[i]->getAverageValueStringData() : ""));
            panelImages[i]->set_text(gridNotes[i]->cutCount != 0 ?  gridNotes[i]->getAverageScoreString() : "");
        }
    }
    void SliceDetailsUI::initScreen(){
        UIScreen = QuestUI::BeatSaberUI::CreateFloatingScreen({40.0f, 32.0f}, {0.0f, 1.0f, 1.0f}, {0, 0, 0}, 0.0f, true, true, 0);
        UIScreen->set_active(false);
        UIScreen->GetComponent<UnityEngine::Canvas*>()->set_sortingOrder(31);
        UnityEngine::GameObject::DontDestroyOnLoad(UIScreen);
        screenhandle = UIScreen->GetComponent<QuestUI::FloatingScreen*>()->handle;
        UIScreen->GetComponent<QuestUI::FloatingScreen*>()->bgGo->GetComponentInChildren<QuestUI::Backgroundable*>()->ApplyBackgroundWithAlpha(il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>("round-rect-panel"), 1.0f);
        screenhandle->get_transform()->set_localPosition(UnityEngine::Vector3(0.0f, -15.0f, 0.0f));
        screenhandle->get_transform()->set_localScale(UnityEngine::Vector3(3.3f, 3.3f, 3.3f));
        QuestUI::FloatingScreen* thing = UIScreen->GetComponent<QuestUI::FloatingScreen*>();

        auto* vert = QuestUI::BeatSaberUI::CreateVerticalLayoutGroup(UIScreen->get_transform());
        auto* line1 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(vert->get_transform());
        auto* line2 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(vert->get_transform());
        auto* line3 = QuestUI::BeatSaberUI::CreateHorizontalLayoutGroup(vert->get_transform());

        line1->set_spacing(8.8f); line2->set_spacing(8.8f); line3->set_spacing(8.8f); vert->set_spacing(-5.5f);

        UINoGlow = QuestUI::ArrayUtil::First(UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Material*>(), [](UnityEngine::Material* x) { return to_utf8(csstrtostr(x->get_name())) == "UINoGlow"; });
        GlobalNamespace::SharedCoroutineStarter::get_instance()->StartCoroutine(reinterpret_cast<custom_types::Helpers::enumeratorT*>(custom_types::Helpers::CoroutineHelper::New(createPanelNotes(line1, line2, line3))));

        auto* screenthingidk = thing->get_gameObject()->AddComponent<HMUI::Screen*>();
        createModalUI(thing->get_transform());
        createGridIndicator(modal->get_transform());

        auto* normalpointer = Resources::FindObjectsOfTypeAll<VRUIControls::VRPointer*>()->get(0);
        hoverClickHelper = SliceDetails::addHoverClickHelper(normalpointer, screenhandle, thing);
        modalHelper = SliceDetails::addModalHelper(normalpointer, thing);
    }

    custom_types::Helpers::Coroutine SliceDetailsUI::createPanelNotes(UI::HorizontalLayoutGroup* line1, UI::HorizontalLayoutGroup* line2, UI::HorizontalLayoutGroup* line3)
    {
        for (int i=0; i<12; i++){
            auto* layout = i<4 ? line1 : i<8 ? line2 : i<12 ? line3 : nullptr;
            panelImages[i] = SliceDetails::CreateClickableImage(layout->get_transform(), "bloq", QuestUI::BeatSaberUI::Base64ToSprite(SliceDetails::Sprites::bloq_gradient), "115", i);
            co_yield nullptr;
        }
        co_return;
    }
    void SliceDetailsUI::refreshNoteData(){
        for (int i = 0; i < 12; i++) {
            delete gridNotes[i];
            gridNotes[i] = new SliceDetails::GridInfo();
	    }
    }
    void SliceDetailsUI::initNoteData(){
        for (int i = 0; i < 12; i++) {
            gridNotes[i] = new SliceDetails::GridInfo();
	    }
    }
    void SliceDetailsUI::onPause(){
        isPaused = true;
        UIScreen->get_transform()->set_position(UnityEngine::Vector3(SliceDetails::Main::config.pausePosX, SliceDetails::Main::config.pausePosY, SliceDetails::Main::config.pausePosZ));
        UIScreen->get_transform()->set_rotation(UnityEngine::Quaternion::Euler(SliceDetails::Main::config.pauseRotX, SliceDetails::Main::config.pauseRotY, SliceDetails::Main::config.pauseRotZ));
        UIScreen->set_active(true);
        modal->Show(false, true, nullptr);
        modal->Hide(false, nullptr);
        
        auto* pausepointer = Resources::FindObjectsOfTypeAll<VRUIControls::VRPointer*>()->get(1);
        auto* mover = pausepointer->get_gameObject()->AddComponent<QuestUI::FloatingScreenMoverPointer*>();
        mover->Init(UIScreen->GetComponent<QuestUI::FloatingScreen*>(), pausepointer);
        hoverClickHelper->vrPointer = pausepointer;
        modalHelper->vrPointer = pausepointer;
        updatePanelImages();
    }
    void SliceDetailsUI::onUnPause(){
        isPaused = false;
        if (UIScreen != nullptr){
            modal->Hide(false, nullptr);
            UIScreen->set_active(false);
        }
    }
    void SliceDetailsUI::onResultsScreenActivate(){
        auto* pointer = Resources::FindObjectsOfTypeAll<VRUIControls::VRPointer*>()->get(0);
        hoverClickHelper->vrPointer = pointer;
        modalHelper->vrPointer = pointer;
        updatePanelImages();
        UIScreen->get_transform()->set_position(UnityEngine::Vector3(SliceDetails::Main::config.resultPosX , SliceDetails::Main::config.resultPosY, SliceDetails::Main::config.resultPosZ));
        UIScreen->get_transform()->set_rotation(UnityEngine::Quaternion::Euler(SliceDetails::Main::config.resultRotX, SliceDetails::Main::config.resultRotY, SliceDetails::Main::config.resultRotZ));
        UIScreen->set_active(true);
        modal->Show(false, true, nullptr);
        modal->Hide(false, nullptr);
    }
    void SliceDetailsUI::onResultsScreenDeactivate(){
        if (UIScreen != nullptr){
            modal->Hide(false, nullptr);
            UIScreen->set_active(false);
        }
    }
}