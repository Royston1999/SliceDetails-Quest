#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "UI/SliceDetailsFloatingScreen.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"
#include "GlobalNamespace/MultiplayerResultsViewController.hpp"
#include "GlobalNamespace/GameServerLobbyFlowCoordinator.hpp"
#include "DelegateUtils.hpp"
#include "System/IDisposable.hpp"
#include "Zenject/IInitializable.hpp"

#define INTERFACES System::IDisposable*, Zenject::IInitializable*

DECLARE_CLASS_CODEGEN_INTERFACES(SliceDetails, MenuController, Il2CppObject, INTERFACES) {
    
    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &::Zenject::IInitializable::Initialize);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &::System::IDisposable::Dispose);
    
    DECLARE_CTOR(ctor, SliceDetails::SliceDetailsFloatingScreen* sliceDetails, GlobalNamespace::ResultsViewController* results, GlobalNamespace::MultiplayerResultsViewController* multiResults);

    public:
    SliceDetails::SliceDetailsFloatingScreen* sliceDetails;
    GlobalNamespace::ResultsViewController* results;
    GlobalNamespace::MultiplayerResultsViewController* multiResults;

    private:
    void OnResultsActivate(bool one, bool two, bool three);
    void OnResultsDeactivate(bool one, bool two);
};

#undef INTERFACES
