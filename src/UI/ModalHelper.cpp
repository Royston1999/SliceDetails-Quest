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
    border = SliceDetails::Main::SliceDetailsUI->hoverStatsPanel;
}

void SliceDetails::ModalHelper::Init(VRUIControls::VRPointer* pointer){
    vrPointer = pointer;
}

void SliceDetails::ModalHelper::Update(){
    if(UnityEngine::Physics::Raycast(vrPointer->get_vrController()->get_position(), vrPointer->get_vrController()->get_forward(), hit, 100)){
        if(static_cast<std::string>(hit.get_collider()->get_name()).compare("modalcollider") == 0 && !SliceDetails::Main::SliceDetailsUI->hoverClickHelper->grabbingHandle){
            if (!isHit){
                int index = std::stoi(static_cast<std::string>(hit.get_collider()->get_transform()->get_parent()->get_name()));
                auto* noteUI = SliceDetails::Main::SliceDetailsUI->modalNotes[index];
                if (SliceDetails::Main::SliceDetailsUI->modal->isShown && noteUI->hoverText != ""){
                    isHit = true;
                    border->get_transform()->SetParent(SliceDetails::Main::SliceDetailsUI->modal->get_transform(), false);
                    border->get_transform()->set_position(hit.get_collider()->get_transform()->get_position() + UnityEngine::Vector3(0.0f, 0.47f, 0.0f));
                    border->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->SetText(noteUI->hoverText);
                    border->get_gameObject()->SetActive(true);
                }
            }
        }
    }
}

void SliceDetails::ModalHelper::LateUpdate(){
    if (isHit && (!hit.get_collider() || static_cast<std::string>(hit.get_collider()->get_name()).compare("modalcollider") != 0)){
        isHit = false;
        border->get_gameObject()->SetActive(false);
    }
}

SliceDetails::ModalHelper* SliceDetails::addModalHelper(VRUIControls::VRPointer* pointer, QuestUI::FloatingScreen* screen){
    auto* helper = screen->get_gameObject()->AddComponent<SliceDetails::ModalHelper*>();
    helper->Init(pointer);
    return helper;
}