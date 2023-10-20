#include "UI/SliceDetailsFloatingScreen.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "SliceDetailsConfig.hpp"
#include "HMUI/CurvedCanvasSettings.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/Shader.hpp"
#include "bsml/shared/BSML/FloatingScreen/FloatingScreenHandleEventArgs.hpp"
#include "bsml/shared/BSML/FloatingScreen/FloatingScreenHandle.hpp"

#include "EasyDelegate.hpp"
#include "bsml/shared/BSML/Components/Backgroundable.hpp"
#include "UnityEngine/Canvas.hpp"
#include "Utils/HandleHighlighter.hpp"
#include "Utils/PanelUIHelper.hpp"
#include "Utils/ModalCloseHandler.hpp"
#include "UnityEngine/UI/RectMask2D.hpp"
#include "Utils/NoteUIHelper.hpp"

DEFINE_TYPE(SliceDetails, SliceDetailsFloatingScreen);

using namespace UnityEngine;

namespace SliceDetails
{

    void SliceDetailsFloatingScreen::ctor(PanelScreenViewController* vc, NoteUIModal* modal, StatsPanel* statsPanel)
    {
        INVOKE_CTOR();
        panelScreen = vc;
        panelScreen->noteUIModal = modal;
        this->statsPanel = statsPanel;
    }

    void SliceDetailsFloatingScreen::Initialize()
    {
        isInitialised = false;
        for (int i = 0; i < 12; i++) {
            gridNotes[i] = new GridInfo();
	    }
    }

    void SliceDetailsFloatingScreen::InitialiseUI()
    {
        if (isInitialised) return;
        floatingScreen = BSML::FloatingScreen::CreateFloatingScreen({40.0f, 32.0f}, true, {0.0f, 1.0f, 1.0f}, Quaternion::Euler({0, 0, 0}), 0, false);
        UnityEngine::Object::Destroy(floatingScreen->get_transform()->GetComponentInChildren<UnityEngine::UI::RectMask2D*>());
        screenhandle = floatingScreen->handle;
        screenhandle->get_transform()->set_localPosition(Vector3(0.0f, -15.0f, 0.0f));
        screenhandle->get_transform()->set_localScale(Vector3(3.3f, 3.3f, 3.3f));
        auto rend = screenhandle->GetComponent<MeshRenderer*>();
        auto mat = Material::New_ctor(Shader::Find("Custom/SimpleLit"));
        mat->set_color(Color::get_white());
        rend->set_material(mat);
        auto canvas = floatingScreen->get_transform()->GetComponentInChildren<Canvas*>();
        canvas->set_sortingOrder(31);
        auto backgroundGo = GameObject::New_ctor("bg");
        backgroundGo->get_transform()->SetParent(floatingScreen->get_transform(), false);
        auto background = backgroundGo->AddComponent<BSML::Backgroundable*>();
        background->ApplyBackground("round-rect-panel");
        background->ApplyAlpha(0.94f);
        reinterpret_cast<RectTransform*>(background->get_transform())->set_sizeDelta(floatingScreen->get_ScreenSize());
        UnityEngine::Object::Destroy(screenhandle->GetComponent<BSML::FloatingScreenHandle*>());
        auto highlight = HandleHighlighter::AddHighlight(this, screenhandle);
        floatingScreen->HandleReleased.addCallback(&SliceDetailsFloatingScreen::UpdateCoordinates, this);

        floatingScreen->SetRootViewController(panelScreen, HMUI::ViewController::AnimationType::None);
        floatingScreen->get_gameObject()->set_active(true);
        floatingScreen->rootViewController->__Activate(false, false);  

        for (auto& panel : panelScreen->panelImages) PanelUIHelper::AddPanelHelper(this, panel);
        for (auto& note : panelScreen->noteUIModal->modalNotes) NoteUIHelper::AddNoteHelper(this, note);
        ModalCloseHandler::AddModalCloser(panelScreen->noteUIModal->modal, highlight, this);
        statsPanel->InitialiseUI(panelScreen->get_transform());
        isInitialised = true;

        UnityEngine::Object::DontDestroyOnLoad(floatingScreen);
        floatingScreen->get_gameObject()->set_active(false);
    }

    void SliceDetailsFloatingScreen::UpdatePanelScreen()
    {
        for (int i = 0; i<12; i++){
            panelScreen->panelImages[i]->hoverText = gridNotes[i]->cutCount != 0 ? gridNotes[i]->getAverageValueStringData() : "";
            panelScreen->panelImages[i]->noteCutText->SetText(gridNotes[i]->cutCount != 0 ?  gridNotes[i]->getAverageScoreString() : "");
        }
    }

    void SliceDetailsFloatingScreen::UpdateNoteInfoUI(int index)
    {
        auto modalNotes = panelScreen->noteUIModal->modalNotes;
        for (int i = 0; i < 18; i++) {
            if (i<12) panelScreen->noteUIModal->gridDots->gridDots[i]->set_color(Color::get_gray());
            if (gridNotes[index]->notes[i]->cutCount != 0){
                float realOffset = (gridNotes[index]->notes[i]->cutOffset / gridNotes[index]->notes[i]->cutCount) * 23.0f;
                float realAngle = (gridNotes[index]->notes[i]->cutAngle / gridNotes[index]->notes[i]->cutCount);
                modalNotes[i]->noteCutArrow->get_gameObject()->set_active(true);
                modalNotes[i]->cutDistanceImage->get_gameObject()->set_active(true);
                
                modalNotes[i]->noteCutArrow->get_transform()->set_localRotation(Quaternion::Euler({0.0f, 0.0f, realAngle}));
                modalNotes[i]->noteCutArrow->get_transform()->set_localPosition({realOffset * (float)std::cos(realAngle * M_PI / 180), realOffset * (float)std::sin(realAngle * M_PI / 180), 0.0f});
                modalNotes[i]->cutDistanceImage->get_transform()->set_localRotation(Quaternion::Euler({0.0f, 0.0f, realAngle}));
                modalNotes[i]->cutDistanceImage->get_transform()->set_localPosition(modalNotes[i]->noteCutArrow->get_transform()->get_localPosition() / 2);
                modalNotes[i]->cutDistanceImage->get_transform()->set_localScale({realOffset / 4.0f, modalNotes[i]->cutDistanceImage->get_transform()->get_localScale().y, 0.0f});
                // modalNotes[i]->cutDistanceImage->set_color(i > 8 ? Color(1.0f-rightHand.r, 1.0f-rightHand.g, 1.0f-rightHand.b, 0.75f) : Color(1.0f-leftHand.r, 1.0f-leftHand.g, 1.0f-leftHand.b, 0.75f));
                modalNotes[i]->noteBackground->set_color(i > 8 ? rightHand : leftHand);
                modalNotes[i]->hoverText = gridNotes[index]->notes[i]->getAverageValueStringData();
            }
            else{
                modalNotes[i]->cutDistanceImage->get_gameObject()->set_active(false);
                modalNotes[i]->hoverText.clear();
                modalNotes[i]->noteBackground->set_color(Color::get_gray());
                modalNotes[i]->noteCutArrow->get_gameObject()->set_active(false);
            }
        }
        panelScreen->noteUIModal->gridDots->gridDots[index]->set_color(Color::get_white());
    }

    void SliceDetailsFloatingScreen::UpdateCoordinates(BSML::FloatingScreen* self, const BSML::FloatingScreenHandleEventArgs& args)
    {
        if (isPaused)
        {
            getSliceDetailsConfig().pausePos.SetValue(args.position);
            getSliceDetailsConfig().pauseRot.SetValue(const_cast<Quaternion&>(args.rotation).get_eulerAngles());
        }
        else
        {
            getSliceDetailsConfig().resultsPos.SetValue(args.position);
            getSliceDetailsConfig().resultsRot.SetValue(const_cast<Quaternion&>(args.rotation).get_eulerAngles());
        }
    }

    void SliceDetailsFloatingScreen::OnPause()
    {
        if (!getSliceDetailsConfig().inPause.GetValue()) return;
        isPaused = true;
        floatingScreen->get_transform()->set_position(getSliceDetailsConfig().pausePos.GetValue());
        floatingScreen->get_transform()->set_rotation(Quaternion::Euler(getSliceDetailsConfig().pauseRot.GetValue()));
        floatingScreen->get_gameObject()->set_active(true);
        panelScreen->noteUIModal->modal->Show(false, true, nullptr);
        panelScreen->noteUIModal->modal->Hide(false, nullptr);
        UpdatePanelScreen();
    }

    void SliceDetailsFloatingScreen::OnUnPause()
    {
        if (!getSliceDetailsConfig().inPause.GetValue()) return;
        isPaused = false;
        panelScreen->noteUIModal->modal->Hide(true, nullptr);
        floatingScreen->get_gameObject()->set_active(false);
    }

    void SliceDetailsFloatingScreen::OnResultsScreenActivate()
    {
        if (!getSliceDetailsConfig().inResults.GetValue()) return;
        floatingScreen->get_transform()->set_position(getSliceDetailsConfig().resultsPos.GetValue());
        floatingScreen->get_transform()->set_rotation(Quaternion::Euler(getSliceDetailsConfig().resultsRot.GetValue()));
        floatingScreen->get_gameObject()->set_active(true);
        panelScreen->noteUIModal->modal->Show(false, true, nullptr);
        panelScreen->noteUIModal->modal->Hide(false, nullptr);
        UpdatePanelScreen();
    }

    void SliceDetailsFloatingScreen::OnResultsScreenDeactivate()
    {
        if (!getSliceDetailsConfig().inResults.GetValue()) return;
        panelScreen->noteUIModal->modal->Hide(true, nullptr);
        floatingScreen->get_gameObject()->set_active(false);
    }

    void SliceDetailsFloatingScreen::ClearNoteData()
    {
        for (int i = 0; i < 12; i++) {
            if (gridNotes[i]) delete gridNotes[i];
            gridNotes[i] = new SliceDetails::GridInfo();
	    }
    }

    bool SliceDetailsFloatingScreen::IsEnabled()
    {
        return getSliceDetailsConfig().inResults.GetValue() || getSliceDetailsConfig().inPause.GetValue();
    }

    void SliceDetailsFloatingScreen::Dispose()
    {
        isInitialised = false;
    }
}