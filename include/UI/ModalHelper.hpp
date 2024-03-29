#pragma once
#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"

#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/Physics.hpp"
#include "UnityEngine/RaycastHit.hpp"
#include "UnityEngine/Collider.hpp"
#include "UnityEngine/Time.hpp"
#include "UnityEngine/Mathf.hpp"
#include "UnityEngine/Resources.hpp"
#include "UI/PanelUI.hpp"
#include "GlobalNamespace/VRController.hpp"
#include "HMUI/HoverHint.hpp"
#include "HMUI/HoverHintController.hpp"
#include "questui/shared/CustomTypes/Components/FloatingScreen/FloatingScreen.hpp"
#include "VRUIControls/VRPointer.hpp"
#include "UnityEngine/UI/Image.hpp"

DECLARE_CLASS_CODEGEN(SliceDetails, ModalHelper, UnityEngine::MonoBehaviour,

    DECLARE_INSTANCE_FIELD(VRUIControls::VRPointer*, vrPointer);
    DECLARE_INSTANCE_FIELD(UnityEngine::RaycastHit, hit);
    DECLARE_INSTANCE_FIELD(UnityEngine::UI::Image*, border);
    DECLARE_INSTANCE_FIELD(bool, isHit);

    DECLARE_INSTANCE_METHOD(void, Init, VRUIControls::VRPointer* pointer);
    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_INSTANCE_METHOD(void, LateUpdate);
);

namespace SliceDetails{
    SliceDetails::ModalHelper* addModalHelper(VRUIControls::VRPointer* pointer, QuestUI::FloatingScreen* screen);
}