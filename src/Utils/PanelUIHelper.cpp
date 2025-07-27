#include "Utils/PanelUIHelper.hpp"
#include "main.hpp"
#include "UnityEngine/Canvas.hpp"
#include "UnityEngine/Resources.hpp"
#include "GlobalNamespace/MenuShockwave.hpp"
#include "UnityEngine/EventSystems/EventSystem.hpp"
#include "VRUIControls/VRInputModule.hpp"

DEFINE_TYPE(SliceDetails, PanelUIHelper);

using namespace UnityEngine;
using HapticPresetSO = Libraries::HM::HMLib::VR::HapticPresetSO;

namespace SliceDetails
{

    GlobalNamespace::Signal* GetImageClickedSignal() {
        static SafePtrUnity<GlobalNamespace::Signal> imageClickedSignal;
        if (!imageClickedSignal) {
            auto menuShockWave = Resources::FindObjectsOfTypeAll<GlobalNamespace::MenuShockwave*>().front_or_default();
            imageClickedSignal = menuShockWave ? menuShockWave->____buttonClickEvents.back_or_default() : nullptr;
        }
        return imageClickedSignal.ptr();
    }

    HapticPresetSO* GetHapticPreset() {
        static SafePtrUnity<HapticPresetSO> imageHapticPreset;
        if (!imageHapticPreset) {
            imageHapticPreset = ScriptableObject::CreateInstance<HapticPresetSO*>();
            imageHapticPreset->____duration = 0.02f;
            imageHapticPreset->____strength = 1.0f;
            imageHapticPreset->____frequency = 0.2f;
            Object::DontDestroyOnLoad(imageHapticPreset.ptr());
        }
        return imageHapticPreset.ptr();
    }

    GlobalNamespace::HapticFeedbackManager* GetHapticController() {
        static SafePtrUnity<GlobalNamespace::HapticFeedbackManager> imageHapticFeedbackController;
        if (!imageHapticFeedbackController) {
            imageHapticFeedbackController = UnityEngine::Object::FindObjectOfType<GlobalNamespace::HapticFeedbackManager*>();
        }
        return imageHapticFeedbackController.ptr();
    }

    VRUIControls::VRPointer* GetVRPointer() {
        static SafePtrUnity<VRUIControls::VRPointer> pointer;
        if (pointer && pointer->get_isActiveAndEnabled()) return pointer.ptr();
        auto currentEventSystem = UnityEngine::EventSystems::EventSystem::get_current();
        if (!currentEventSystem) return nullptr;
        auto vrInputModule = currentEventSystem->get_currentInputModule().try_cast<VRUIControls::VRInputModule>().value_or(nullptr);
        if (!vrInputModule) return nullptr;

        pointer = vrInputModule->____vrPointer;
        return pointer.ptr();
    }

    void PanelUIHelper::Vibrate(bool left)
    {
        XR::XRNode node = left ? XR::XRNode::LeftHand : XR::XRNode::RightHand;
        GetHapticController()->PlayHapticFeedback(node, GetHapticPreset());
    }

    void PanelUIHelper::UnFuckModal()
    {
        auto* self = sliceDetails->panelScreen->noteUIModal->modal;
        auto cm = self->get_gameObject()->GetComponent<Canvas*>();
        cm->set_overrideSorting(false); 
        cm->set_sortingOrder(31);
    }

    PanelUIHelper* PanelUIHelper::AddPanelHelper(SliceDetailsFloatingScreen* screen, PanelUI* panelUI)
    {
        auto helper = panelUI->collider->get_gameObject()->AddComponent<PanelUIHelper*>();
        helper->sliceDetails = screen;
        helper->panel = panelUI;
        helper->buttonClickedSignal = GetImageClickedSignal();
        return helper;
    }

    void PanelUIHelper::OnPointerEnter()
    {
        if (sliceDetails->gridNotes[panel->index]->getCombinedNoteInfo().cutCount == 0) return;
        if (sliceDetails->grabbingHandle) return;
        Vibrate(!GetVRPointer()->____lastSelectedControllerWasRight);
        panel->background->set_color(Color(0.70f, 0.70f, 0.70f, 1.0f));
        sliceDetails->statsPanel->ActivatePanel(sliceDetails->panelScreen->get_transform(), panel->collider->get_transform()->get_position(), panel->hoverText);
    }

    void PanelUIHelper::OnPointerClick()
    {
        if (sliceDetails->gridNotes[panel->index]->getCombinedNoteInfo().cutCount == 0) return;
        if (buttonClickedSignal) buttonClickedSignal->Raise();
        sliceDetails->UpdateNoteInfoUI(panel->index);
        sliceDetails->panelScreen->noteUIModal->modal->Show(true, true, nullptr);
        UnFuckModal();
        sliceDetails->statsPanel->DeactivatePanel();
    }

    void PanelUIHelper::OnPointerExit()
    {
        panel->background->set_color(Color::get_gray());
        sliceDetails->statsPanel->DeactivatePanel();
    }

}