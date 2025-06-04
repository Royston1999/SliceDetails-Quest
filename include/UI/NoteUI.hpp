#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "bsml/shared/macros.hpp"
#include "bsml/shared/BSML/FloatingScreen/FloatingScreen.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "HMUI/ModalView.hpp"
#include "UI/GridDotsViewController.hpp"
#include "UI/NoteUI.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/BoxCollider.hpp"
#include "HMUI/ImageView.hpp"
#include "HMUI/StackLayoutGroup.hpp"
#include "System/Object.hpp"

DECLARE_CLASS_CODEGEN(SliceDetails, NoteUI, System::Object) {

    DECLARE_CTOR(ctor, int rotation, int index);
    DECLARE_INSTANCE_METHOD(void, PostParse);

    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, bloqLayout);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, noteBackground);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, noteArrow);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, noteCutArrow);
    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, cutDistanceImage);

    public:
    UnityEngine::BoxCollider* collider; // might not be needed
    std::string hoverText;
    int rot;
    int index;
};
