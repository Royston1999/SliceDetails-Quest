#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "bsml/shared/macros.hpp"
#include "bsml/shared/BSML/FloatingScreen/FloatingScreen.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "HMUI/ViewController.hpp"
#include "HMUI/ImageView.hpp"
#include "System/IDisposable.hpp"
#include "Zenject/IInitializable.hpp"

#define INTERFACES System::IDisposable*, Zenject::IInitializable*

DECLARE_CLASS_CODEGEN_INTERFACES(SliceDetails, GridDotsViewController, HMUI::ViewController, INTERFACES) {
    
    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &::HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    public:
    HMUI::ImageView* gridDots[12];
};

#undef INTERFACES
