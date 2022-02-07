#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Physics.hpp"
#include "UnityEngine/RaycastHit.hpp"
#include "UnityEngine/Collider.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/Mathf.hpp"
#include "UI/HoverClickHelper.hpp"
#include "GlobalNamespace/VRController.hpp"
#include "HMUI/ModalView.hpp"
#include "VRUIControls/VRPointer.hpp"
#include "UnityEngine/Shader.hpp"
#include "SliceDetailsUI.hpp"
#include "UnityEngine/Space.hpp"
#include "main.hpp"

DEFINE_TYPE(SliceDetails, HoverClickHelper);

void SliceDetails::HoverClickHelper::Awake(){
    isHit = false;
    hintController = QuestUI::ArrayUtil::First(UnityEngine::Resources::FindObjectsOfTypeAll<HMUI::HoverHintController*>());
    panelUI = nullptr;
    notClickedModal = true;
    outOfRange = false;
    currentCollider = nullptr;
    grabbingHandle = false;
    hoveringHandle = false;
    hoverHandleMat = UnityEngine::Material::New_ctor(UnityEngine::Shader::Find(il2cpp_utils::newcsstr("Hidden/Internal-DepthNormalsTexture")));
}

void SliceDetails::HoverClickHelper::Init(VRUIControls::VRPointer* pointer, UnityEngine::GameObject* handle){
    vrPointer = pointer;
    handleTransform = handle;
    origHandleMat = handle->GetComponent<UnityEngine::MeshRenderer*>()->get_material();
}

void SliceDetails::HoverClickHelper::Update(){
    if(UnityEngine::Physics::Raycast(vrPointer->get_vrController()->get_position(), vrPointer->get_vrController()->get_forward(), hit, 100)){
        if(to_utf8(csstrtostr(hit.get_collider()->get_name())).substr(0, 12).compare("gridcollider") == 0 && !grabbingHandle){
            if (isHit && currentCollider && currentCollider != hit.get_collider()->get_transform()){
                panelUI->image->GetComponent<UnityEngine::UI::Image*>()->set_color(UnityEngine::Color::get_gray());
                hintController->hoverHintPanel->Hide();
                panelUI = nullptr;
                isHit = false;
            }
            if (!isHit){
                panelUI = SliceDetails::Main::SliceDetailsUI->panelImages[std::stoi(to_utf8(csstrtostr(hit.get_collider()->get_name())).substr(13, 2))];
                currentCollider = hit.get_collider()->get_transform();
                if (!SliceDetails::Main::SliceDetailsUI->modal->isShown && SliceDetails::Main::SliceDetailsUI->gridNotes[panelUI->index]->cutCount != 0){
                    isHit = true;
                    panelUI->image->set_color(UnityEngine::Color(0.70f, 0.70f, 0.70f, 1.0f));
                    hintController->SetupAndShowHintPanel(panelUI->hoverHint);
                    panelUI->hoverHint->set_enabled(true);
                    panelUI->hoverHint->get_gameObject()->set_active(true);
                    hintController->hoverHintPanel->get_transform()->set_localScale({0.6f, 0.6f, 0.0f});
                    hintController->hoverHintPanel->get_transform()->set_position(panelUI->hoverHint->get_transform()->get_position());
                    hintController->hoverHintPanel->get_transform()->Translate({0.0f, 0.21f, 0.0f}, UnityEngine::Space::Self);
                }
                else panelUI = nullptr;
            }
        }
        else if (isHit && !SliceDetails::Main::SliceDetailsUI->modal->isShown){
            panelUI->image->set_color(UnityEngine::Color::get_gray());
            hintController->hoverHintPanel->Hide();
            panelUI = nullptr;
            isHit = false;
        }
        if(hit.get_collider()->get_transform() == handleTransform->get_transform()){
            if(!hoveringHandle){
                hoveringHandle = true;
                handleTransform->GetComponent<UnityEngine::MeshRenderer*>()->set_material(hoverHandleMat);
            }
        }
        else if(hoveringHandle && !grabbingHandle){
            hoveringHandle = false;
            handleTransform->GetComponent<UnityEngine::MeshRenderer*>()->set_material(origHandleMat);
        }
    }
    else {
        if (isHit && !SliceDetails::Main::SliceDetailsUI->modal->isShown){
            panelUI->image->GetComponent<UnityEngine::UI::Image*>()->set_color(UnityEngine::Color::get_gray());
            hintController->hoverHintPanel->Hide();
            panelUI = nullptr;
            isHit = false;
        }
        if(hoveringHandle && !grabbingHandle){
            hoveringHandle = false;
            handleTransform->GetComponent<UnityEngine::MeshRenderer*>()->set_material(origHandleMat);
        }
    }
    if (isHit && grabbingController && !modalLocked && notClickedModal && !justClosedModal && !outOfRange){
        grabbingController = vrPointer->get_vrController();
        triggerPressed = true;
        notClickedModal = false;
        panelUI->image->set_color(UnityEngine::Color::get_gray());
        SliceDetails::Main::SliceDetailsUI->updateGridNotesInfo(panelUI->index);
        SliceDetails::Main::SliceDetailsUI->modal->Show(true, true, nullptr);
        hintController->hoverHintPanel->Hide();
        panelUI = nullptr;
        isHit = false;
        modalLocked = true;
    }
    if (!SliceDetails::Main::SliceDetailsUI->modal->isShown && !modalLocked && !notClickedModal) notClickedModal = true;
    if (justClosedModal) modalLocked = false;
    if (grabbingController) outOfRange = true;
}

void SliceDetails::HoverClickHelper::LateUpdate(){
    if(!triggerPressed && !isHit && vrPointer->get_vrController()->get_triggerValue() > 0.9f && !(hoveringHandle || grabbingHandle)){
        SliceDetails::Main::SliceDetailsUI->modal->Hide(true, nullptr);
        justClosedModal = true;
    }
    if (vrPointer->get_vrController()->get_triggerValue() > 0.9f && !triggerPressed){
        grabbingController = vrPointer->get_vrController();
        triggerPressed = true;
        if ((hit.get_collider() && hit.get_collider()->get_transform() == handleTransform->get_transform())){
            handleTransform->GetComponent<UnityEngine::MeshRenderer*>()->set_material(hoverHandleMat);
            grabbingHandle = true;
            hoveringHandle = true;
        }
    }
    if (triggerPressed && grabbingController->get_triggerValue() < 0.1f){
        if (grabbingHandle){
            auto* screenTransform = handleTransform->get_transform()->get_parent();
            if ((float)(screenTransform->get_position().y) < 0.5) screenTransform->Translate(0.0f, (0.5 - screenTransform->get_position().y), 0.0f, UnityEngine::Space::World);
            SliceDetails::Main::SliceDetailsUI->updateCoordinates(screenTransform);
        }
        grabbingController = nullptr;
        triggerPressed = false;
        justClosedModal = false;
        outOfRange = false;
        grabbingHandle = false;
    } 
    if (isHit && SliceDetails::Main::SliceDetailsUI->modal->isShown) isHit = false; 
    
}

void SliceDetails::HoverClickHelper::resetBools(){
    justClosedModal = false;
    notClickedModal = true;
    triggerPressed = false;
    modalLocked = false;
    grabbingController = nullptr;
    outOfRange = false;
}

SliceDetails::HoverClickHelper* SliceDetails::addHoverClickHelper(VRUIControls::VRPointer* pointer, UnityEngine::GameObject* handle, QuestUI::FloatingScreen* screen){
    auto* helper = screen->get_gameObject()->AddComponent<SliceDetails::HoverClickHelper*>();
    helper->Init(pointer, handle);
    return helper;
}