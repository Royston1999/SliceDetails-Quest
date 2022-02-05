#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Physics.hpp"
#include "UnityEngine/RaycastHit.hpp"
#include "UnityEngine/Collider.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/Mathf.hpp"
#include "UI/ModalHelper.hpp"
#include "GlobalNamespace/VRController.hpp"
#include "HMUI/ModalView.hpp"
#include "VRUIControls/VRPointer.hpp"
#include "UnityEngine/Space.hpp"
#include "main.hpp"

DEFINE_TYPE(SliceDetails, ModalHelper);

void SliceDetails::ModalHelper::Awake(){
    isHit = false;
    hintController = QuestUI::ArrayUtil::First(UnityEngine::Resources::FindObjectsOfTypeAll<HMUI::HoverHintController*>());
    hint = nullptr;
}

void SliceDetails::ModalHelper::Init(VRUIControls::VRPointer* pointer){
    vrPointer = pointer;
}

void SliceDetails::ModalHelper::Update(){
    if(UnityEngine::Physics::Raycast(vrPointer->get_vrController()->get_position(), vrPointer->get_vrController()->get_forward(), hit, 100)){
        if(to_utf8(csstrtostr(hit.get_collider()->get_name())).compare("modalcollider") == 0){
            if (!isHit){
                hint = hit.get_collider()->get_transform()->get_parent()->GetComponentInChildren<HMUI::HoverHint*>();
                if (SliceDetails::Main::SliceDetailsUI->modal->isShown){
                    isHit = true;
                    hintController->SetupAndShowHintPanel(hint);
                    hint->set_enabled(true);
                    hint->get_gameObject()->set_active(true);
                    hintController->hoverHintPanel->get_transform()->SetParent(SliceDetails::Main::SliceDetailsUI->modal->get_transform(), false);
                    hintController->hoverHintPanel->get_transform()->set_localScale({0.6f, 0.6f, 0.0f});
                    hintController->hoverHintPanel->get_transform()->set_position(hint->get_transform()->get_position());
                    hintController->hoverHintPanel->get_transform()->Translate({0.0f, 0.21f, 0.0f}, UnityEngine::Space::Self);
                }
            }
        }
    }
}

void SliceDetails::ModalHelper::LateUpdate(){
    if (isHit && (!hit.get_collider() || to_utf8(csstrtostr(hit.get_collider()->get_name())).compare("modalcollider") != 0)){
        isHit = false;
        hintController->hoverHintPanel->Hide();
        hint = nullptr;
    }
}

SliceDetails::ModalHelper* SliceDetails::addModalHelper(VRUIControls::VRPointer* pointer, QuestUI::FloatingScreen* screen){
    auto* helper = screen->get_gameObject()->AddComponent<SliceDetails::ModalHelper*>();
    helper->Init(pointer);
    return helper;
}