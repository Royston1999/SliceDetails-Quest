#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "bsml/shared/macros.hpp"
#include "bsml/shared/BSML/FloatingScreen/FloatingScreen.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UI/SliceDetailsFloatingScreen.hpp"
#include "Data/GridInfo.hpp"
#include "UnityEngine/Color.hpp"
#include "GlobalNamespace/GamePause.hpp"
#include "DelegateUtils.hpp"
#include "System/Action.hpp"
#include "System/IDisposable.hpp"
#include "Zenject/IInitializable.hpp"

#define INTERFACES System::IDisposable*, Zenject::IInitializable*

DECLARE_CLASS_CODEGEN_INTERFACES(SliceDetails, PauseController, Il2CppObject, INTERFACES) {
    
    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &::Zenject::IInitializable::Initialize);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &::System::IDisposable::Dispose);
    
    DECLARE_CTOR(ctor, SliceDetails::SliceDetailsFloatingScreen* sliceDetails, GlobalNamespace::IGamePause* gamePause);

    public:
    SliceDetails::SliceDetailsFloatingScreen* sliceDetails;
    GlobalNamespace::GamePause* gamePause;

    private:
    void OnPause();
    void OnUnPause();
};

#undef INTERFACES
