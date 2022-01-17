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
#include "UI/ClickableImage.hpp"
#include "GlobalNamespace/VRController.hpp"
#include "HMUI/HoverHintController.hpp"
#include "VRUIControls/VRPointer.hpp"

DECLARE_CLASS_CODEGEN(SliceDetails, ModalHelper, UnityEngine::MonoBehaviour,

    DECLARE_INSTANCE_FIELD(VRUIControls::VRPointer*, vrPointer);
    DECLARE_INSTANCE_FIELD(HMUI::HoverHint*, hint);
    DECLARE_INSTANCE_FIELD(UnityEngine::RaycastHit, hit);
    DECLARE_INSTANCE_FIELD(HMUI::HoverHintController*, hintController);
    DECLARE_INSTANCE_FIELD(bool, isHit);

    DECLARE_INSTANCE_METHOD(void, Init, VRUIControls::VRPointer* pointer);
    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, Update);
    DECLARE_INSTANCE_METHOD(void, LateUpdate);

    

    public:
        static GlobalNamespace::VRController* grabbingController;
        static bool triggerPressed;
);

namespace SliceDetails{
    void addModalHelper(VRUIControls::VRPointer* pointer);
}