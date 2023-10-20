#pragma once

#include "System/IDisposable.hpp"
#include "Zenject/IInitializable.hpp"
#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "bsml/shared/macros.hpp"
#include "bsml/shared/BSML/FloatingScreen/FloatingScreen.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "HMUI/ViewController.hpp"
#include "UI/NoteUIModal.hpp"
#include "UI/PanelUI.hpp"

DECLARE_CLASS_CODEGEN(SliceDetails, PanelScreenViewController, HMUI::ViewController,

    DECLARE_OVERRIDE_METHOD(void, DidActivate, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::HMUI::ViewController::DidActivate>::get(), bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    DECLARE_INSTANCE_FIELD(NoteUIModal*, noteUIModal);
    DECLARE_INSTANCE_FIELD(BSML::FloatingScreen*, floatingScreen);

    public:
    SliceDetails::PanelUI* panelImages[12];
)