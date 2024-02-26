#include "Utils/PanelUIHelper.hpp"
#include "main.hpp"
#include "UnityEngine/Canvas.hpp"
#include "UnityEngine/Resources.hpp"
#include "GlobalNamespace/MenuShockwave.hpp"

DEFINE_TYPE(SliceDetails, PanelUIHelper);

using namespace UnityEngine;
using HapticPresetSO = Libraries::HM::HMLib::VR::HapticPresetSO;

namespace SliceDetails
{

    GlobalNamespace::Signal* GetImageClickedSignal() {
        static SafePtrUnity<GlobalNamespace::Signal> imageClickedSignal;
        if (!imageClickedSignal) {
            auto menuShockWave = Resources::FindObjectsOfTypeAll<GlobalNamespace::MenuShockwave*>().FirstOrDefault();
            imageClickedSignal = menuShockWave ? menuShockWave->buttonClickEvents.LastOrDefault() : nullptr;
        }
        return imageClickedSignal.ptr();
    }

    HapticPresetSO* GetHapticPreset() {
        static SafePtrUnity<HapticPresetSO> imageHapticPreset;
        if (!imageHapticPreset) {
            imageHapticPreset = ScriptableObject::CreateInstance<HapticPresetSO*>();
            imageHapticPreset->duration = 0.02f;
            imageHapticPreset->strength = 1.0f;
            imageHapticPreset->frequency = 0.2f;
            Object::DontDestroyOnLoad(imageHapticPreset.ptr());
        }
        return imageHapticPreset.ptr();
    }

    GlobalNamespace::HapticFeedbackController* GetHapticController() {
        static SafePtrUnity<GlobalNamespace::HapticFeedbackController> imageHapticFeedbackController;
        if (!imageHapticFeedbackController) {
            imageHapticFeedbackController = UnityEngine::Object::FindObjectOfType<GlobalNamespace::HapticFeedbackController*>();
        }
        return imageHapticFeedbackController.ptr();
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
        if (sliceDetails->gridNotes[panel->index]->cutCount == 0) return;
        if (sliceDetails->grabbingHandle) return;
        Vibrate(!VRUIControls::VRPointer::_get__lastControllerUsedWasRight());
        panel->background->set_color(Color(0.70f, 0.70f, 0.70f, 1.0f));
        sliceDetails->statsPanel->ActivatePanel(sliceDetails->panelScreen->get_transform(), panel->collider->get_transform()->get_position(), panel->hoverText);
    }

    void PanelUIHelper::OnPointerClick()
    {
        if (sliceDetails->gridNotes[panel->index]->cutCount == 0) return;
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