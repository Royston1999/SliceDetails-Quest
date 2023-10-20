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

    GlobalNamespace::Signal* get_imageClickedSignal() {
        static SafePtrUnity<GlobalNamespace::Signal> imageClickedSignal;
        if (!imageClickedSignal) {
            auto menuShockWave = Resources::FindObjectsOfTypeAll<GlobalNamespace::MenuShockwave*>().FirstOrDefault();
            imageClickedSignal = menuShockWave ? menuShockWave->buttonClickEvents.LastOrDefault() : nullptr;
        }
        return imageClickedSignal.ptr();
    }

    HapticPresetSO* get_imageHapticPreset() {
        static SafePtrUnity<HapticPresetSO> imageHapticPreset;
        if (!imageHapticPreset) {
            imageHapticPreset = UnityEngine::ScriptableObject::CreateInstance<HapticPresetSO*>();
            imageHapticPreset->duration = 0.02f;
            imageHapticPreset->strength = 1.0f;
            imageHapticPreset->frequency = 0.2f;
            Object::DontDestroyOnLoad(imageHapticPreset.ptr());
        }
        return imageHapticPreset.ptr();
    }

    GlobalNamespace::HapticFeedbackController* get_imageHapticFeedbackController() {
        static SafePtrUnity<GlobalNamespace::HapticFeedbackController> imageHapticFeedbackController;
        if (!imageHapticFeedbackController) {
            imageHapticFeedbackController = UnityEngine::Object::FindObjectOfType<GlobalNamespace::HapticFeedbackController*>();
        }
        return imageHapticFeedbackController.ptr();
    }

    void PanelUIHelper::Vibrate(bool left)
    {
        getLogger().info("i'm so confused");
        UnityEngine::XR::XRNode node = left ? UnityEngine::XR::XRNode::LeftHand : UnityEngine::XR::XRNode::RightHand;
        get_imageHapticFeedbackController()->PlayHapticFeedback(node, get_imageHapticPreset());
        getLogger().info("just in cunt");
    }

    PanelUIHelper* PanelUIHelper::AddPanelHelper(SliceDetailsFloatingScreen* screen, PanelUI* panelUI)
    {
        auto helper = panelUI->collider->get_gameObject()->AddComponent<PanelUIHelper*>();
        helper->sliceDetails = screen;
        helper->panel = panelUI;
        helper->hapticFeedbackController = get_imageHapticFeedbackController();
        helper->hapticFeedbackPresetSO = get_imageHapticPreset();
        helper->buttonClickedSignal = get_imageClickedSignal();
        return helper;
    }

    void PanelUIHelper::OnPointerEnter()
    {
        if (sliceDetails->gridNotes[panel->index]->cutCount == 0) return;
        if (sliceDetails->grabbingHandle) return;
        Vibrate(!VRUIControls::VRPointer::_get__lastControllerUsedWasRight());
        panel->background->set_color(UnityEngine::Color(0.70f, 0.70f, 0.70f, 1.0f));
        sliceDetails->statsPanel->ActivatePanel(sliceDetails->panelScreen->get_transform(), panel->collider->get_transform()->get_position(), panel->hoverText);
    }

    void PanelUIHelper::OnPointerClick()
    {
        if (sliceDetails->gridNotes[panel->index]->cutCount == 0) return;
        if (buttonClickedSignal) buttonClickedSignal->Raise();
        sliceDetails->UpdateNoteInfoUI(panel->index);
        sliceDetails->panelScreen->noteUIModal->modal->Show(true, true, nullptr);
        auto* self = sliceDetails->panelScreen->noteUIModal->modal;
        auto cm = self->get_gameObject()->GetComponent<UnityEngine::Canvas*>();
        cm->set_overrideSorting(false); 
        cm->set_sortingOrder(31);
        sliceDetails->statsPanel->DeactivatePanel();
    }

    void PanelUIHelper::OnPointerExit()
    {
        panel->background->set_color(UnityEngine::Color::get_gray());
        sliceDetails->statsPanel->DeactivatePanel();
    }

}