#pragma once

#include "System/IDisposable.hpp"
#include "Zenject/IInitializable.hpp"
#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "bsml/shared/macros.hpp"
#include "bsml/shared/BSML/FloatingScreen/FloatingScreen.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UI/SliceDetailsFloatingScreen.hpp"
#include "Data/GridInfo.hpp"
#include "UnityEngine/Color.hpp"
#include "GlobalNamespace/IGamePause.hpp"
#include "GlobalNamespace/ResultsViewController.hpp"
#include "GlobalNamespace/MultiplayerResultsViewController.hpp"
#include "GlobalNamespace/GameServerLobbyFlowCoordinator.hpp"

#define INTERFACES {classof(System::IDisposable*), classof(Zenject::IInitializable*)} \

DECLARE_CLASS_CODEGEN_INTERFACES(SliceDetails, MenuController, Il2CppObject, std::vector<Il2CppClass*>(INTERFACES),
    
    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());
    
    DECLARE_CTOR(ctor, SliceDetails::SliceDetailsFloatingScreen* sliceDetails, GlobalNamespace::ResultsViewController* results, GlobalNamespace::MultiplayerResultsViewController* multiResults, GlobalNamespace::GameServerLobbyFlowCoordinator* multiLobby);

    public:
    SliceDetails::SliceDetailsFloatingScreen* sliceDetails;
    GlobalNamespace::ResultsViewController* results;
    GlobalNamespace::MultiplayerResultsViewController* multiResults;
    GlobalNamespace::GameServerLobbyFlowCoordinator* multiLobby;

    private:
    void OnResultsActivate(bool one, bool two, bool three);
    void OnResultsDeActivate(bool one, bool two);
)

#undef INTERFACES