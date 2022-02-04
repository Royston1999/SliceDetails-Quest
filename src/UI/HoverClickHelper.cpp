#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Physics.hpp"
#include "UnityEngine/RaycastHit.hpp"
#include "UnityEngine/Collider.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/Mathf.hpp"
#include "UI/HoverClickHelper.hpp"
#include "GlobalNamespace/VRController.hpp"
#include "questui/shared/CustomTypes/Components/FloatingScreen/FloatingScreen.hpp"
#include "HMUI/ModalView.hpp"
#include "VRUIControls/VRPointer.hpp"
#include "UnityEngine/Shader.hpp"
#include "UIUtils.hpp"
#include "UnityEngine/Space.hpp"
#include "main.hpp"

DEFINE_TYPE(SliceDetails, HoverClickHelper);

void SliceDetails::HoverClickHelper::Awake(){
    isHit = false;
    hintController = QuestUI::ArrayUtil::First(UnityEngine::Resources::FindObjectsOfTypeAll<HMUI::HoverHintController*>());
    clickimg = nullptr;
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
        if(to_utf8(csstrtostr(hit.get_collider()->get_name())).compare("gridcollider") == 0){
            if (isHit && currentCollider && currentCollider != hit.get_collider()->get_transform()){
                clickimg->image->GetComponent<UnityEngine::UI::Image*>()->set_color(UnityEngine::Color::get_gray());
                hintController->hoverHintPanel->Hide();
                clickimg = nullptr;
                isHit = false;
            }
            if (!isHit){
                clickimg = hit.get_collider()->get_transform()->get_parent()->GetComponent<SliceDetails::ClickableImage*>();
                currentCollider = hit.get_collider()->get_transform();
                if (!SliceDetails::Main::SliceDetailsUI->modal->isShown && SliceDetails::Main::SliceDetailsUI->gridNotes[clickimg->index]->cutCount != 0){
                    isHit = true;
                    clickimg->image->GetComponent<UnityEngine::UI::Image*>()->set_color(UnityEngine::Color(0.70f, 0.70f, 0.70f, 1.0f));
                    hintController->SetupAndShowHintPanel(clickimg->theHint);
                    clickimg->theHint->set_enabled(true);
                    clickimg->theHint->get_gameObject()->set_active(true);
                    hintController->hoverHintPanel->get_transform()->set_localScale({0.5f, 0.5f, 0.0f});
                    hintController->hoverHintPanel->get_transform()->set_position(clickimg->theHint->get_transform()->get_position());
                    hintController->hoverHintPanel->get_transform()->Translate({0.0f, 0.21f, 0.0f}, UnityEngine::Space::Self);
                }
                else clickimg = nullptr;
            }
        }
        else if (isHit && !SliceDetails::Main::SliceDetailsUI->modal->isShown){
            clickimg->image->GetComponent<UnityEngine::UI::Image*>()->set_color(UnityEngine::Color::get_gray());
            hintController->hoverHintPanel->Hide();
            clickimg = nullptr;
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
            clickimg->image->GetComponent<UnityEngine::UI::Image*>()->set_color(UnityEngine::Color::get_gray());
            hintController->hoverHintPanel->Hide();
            clickimg = nullptr;
            isHit = false;
        }
        if(hoveringHandle && !grabbingHandle){
            hoveringHandle = false;
            handleTransform->GetComponent<UnityEngine::MeshRenderer*>()->set_material(origHandleMat);        }
    }
    if (isHit && grabbingController && notClickedModal && !justClosedModal && !outOfRange && !SliceDetails::Main::SliceDetailsUI->modal->isShown && SliceDetails::Main::SliceDetailsUI->gridNotes[clickimg->index]->cutCount != 0){
        SliceDetails::HoverClickHelper::grabbingController = vrPointer->get_vrController();
        SliceDetails::HoverClickHelper::triggerPressed = true;
        notClickedModal = false;
        clickimg->image->GetComponent<UnityEngine::UI::Image*>()->set_color(UnityEngine::Color::get_gray());
        SliceDetails::Main::SliceDetailsUI->updateGridNotesInfo(clickimg->index);
        SliceDetails::Main::SliceDetailsUI->modal->Show(true, true, nullptr);
        hintController->hoverHintPanel->Hide();
        clickimg = nullptr;
        isHit = false;
    }
    if (SliceDetails::HoverClickHelper::grabbingController){
        outOfRange = true;
    }
}

void SliceDetails::HoverClickHelper::LateUpdate(){
    if(!SliceDetails::HoverClickHelper::triggerPressed && !isHit && vrPointer->get_vrController()->get_triggerValue() > 0.9f && SliceDetails::Main::SliceDetailsUI->modal->isShown &&  ((hit.get_collider() && hit.get_collider()->get_transform() != handleTransform->get_transform()) || !hit.get_collider())){
        SliceDetails::Main::SliceDetailsUI->modal->Hide(true, nullptr);
        justClosedModal = true;
    }
    if (vrPointer->get_vrController()->get_triggerValue() > 0.9f && !SliceDetails::HoverClickHelper::triggerPressed){
        SliceDetails::HoverClickHelper::grabbingController = vrPointer->get_vrController();
        SliceDetails::HoverClickHelper::triggerPressed = true;
        if ((hit.get_collider() && hit.get_collider()->get_transform() == handleTransform->get_transform())){
            handleTransform->GetComponent<UnityEngine::MeshRenderer*>()->set_material(hoverHandleMat);
            grabbingHandle = true;
            hoveringHandle = true;
        }
    }
    if (SliceDetails::HoverClickHelper::triggerPressed && SliceDetails::HoverClickHelper::grabbingController->get_triggerValue() < 0.1f){
        if (grabbingHandle){
            auto* screenTransform = handleTransform->get_transform()->get_parent();
            if ((float)(screenTransform->get_position().y) < 0.5) screenTransform->Translate(0.0f, (0.5 - screenTransform->get_position().y), 0.0f, UnityEngine::Space::World);
            if (SliceDetails::Main::isPaused){
                setFloat(getConfig().config, "pausePosX", screenTransform->get_position().x);
                setFloat(getConfig().config, "pausePosY", screenTransform->get_position().y);
                setFloat(getConfig().config, "pausePosZ", screenTransform->get_position().z);
                getConfig().Write();
                setFloat(getConfig().config, "pauseRotX", screenTransform->get_rotation().get_eulerAngles().x);
                setFloat(getConfig().config, "pauseRotY", screenTransform->get_rotation().get_eulerAngles().y);
                setFloat(getConfig().config, "pauseRotZ", screenTransform->get_rotation().get_eulerAngles().z);
                getConfig().Write();
            }
            else{
                setFloat(getConfig().config, "resultPosX", screenTransform->get_position().x);
                setFloat(getConfig().config, "resultPosY", screenTransform->get_position().y);
                setFloat(getConfig().config, "resultPosZ", screenTransform->get_position().z);
                getConfig().Write();
                setFloat(getConfig().config, "resultRotX", screenTransform->get_rotation().get_eulerAngles().x);
                setFloat(getConfig().config, "resultRotY", screenTransform->get_rotation().get_eulerAngles().y);
                setFloat(getConfig().config, "resultRotZ", screenTransform->get_rotation().get_eulerAngles().z);
                getConfig().Write();
            }
            ConfigHelper::LoadConfig(SliceDetails::Main::config, getConfig().config);
        }
        SliceDetails::HoverClickHelper::grabbingController = nullptr;
        SliceDetails::HoverClickHelper::triggerPressed = false;
        justClosedModal = false;
        outOfRange = false;
        grabbingHandle = false;
    } 
    if (isHit && SliceDetails::Main::SliceDetailsUI->modal->isShown) isHit = false; 
    if (!notClickedModal && !SliceDetails::Main::SliceDetailsUI->modal->isShown) notClickedModal = true;
    
}

void SliceDetails::addHoverClickHelper(VRUIControls::VRPointer* pointer, UnityEngine::GameObject* handle){
    auto* helper = pointer->get_gameObject()->AddComponent<SliceDetails::HoverClickHelper*>();
    helper->Init(pointer, handle);
}