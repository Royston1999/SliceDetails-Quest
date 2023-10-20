#pragma once

#include "System/IDisposable.hpp"
#include "Zenject/IInitializable.hpp"
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
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"

DECLARE_CLASS_CODEGEN(SliceDetails, NoteUIModal, Il2CppObject,

    DECLARE_INSTANCE_FIELD(HMUI::ModalView*, modal);

    DECLARE_INSTANCE_METHOD(void, InitialiseUI, UnityEngine::Transform* parent);
    DECLARE_INSTANCE_METHOD(void, PostParse);

    DECLARE_CTOR(ctor, SliceDetails::GridDotsViewController* dots);

    public:
    SliceDetails::NoteUI* modalNotes[18];
    UnityEngine::Color leftHand;
    UnityEngine::Color rightHand;
    SliceDetails::GridDotsViewController* gridDots;
)

