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

DECLARE_CLASS_CODEGEN(SliceDetails, StatsPanel, Il2CppObject,

    DECLARE_INSTANCE_FIELD(HMUI::ImageView*, border);
    DECLARE_INSTANCE_FIELD(TMPro::TextMeshProUGUI*, text);
    DECLARE_DEFAULT_CTOR();

    DECLARE_INSTANCE_METHOD(void, PostParse);

    public:
    void ActivatePanel(UnityEngine::Transform* parent, UnityEngine::Vector3 position, std::string text);
    void DeactivatePanel();
    void InitialiseUI(UnityEngine::Transform* parent);
)

