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
#include "GlobalNamespace/NoteController.hpp"
#include "GlobalNamespace/NoteCutInfo.hpp"
#include "GlobalNamespace/CutScoreBuffer.hpp"
#include "GlobalNamespace/IScoreController.hpp"
#include "GlobalNamespace/ScoreController.hpp"
#include "GlobalNamespace/NoteData.hpp"
#include <map>
#include "GlobalNamespace/ColorScheme.hpp"
#include "DelegateUtils.hpp"
#include "System/Action_1.hpp"

#define INTERFACES {classof(System::IDisposable*), classof(Zenject::IInitializable*)} \

DECLARE_CLASS_CODEGEN_INTERFACES(SliceDetails, GameCoreController, Il2CppObject, std::vector<Il2CppClass*>(INTERFACES),
    
    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
    DECLARE_OVERRIDE_METHOD(void, Dispose, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::System::IDisposable::Dispose>::get());
    
    DECLARE_CTOR(ctor, SliceDetails::SliceDetailsFloatingScreen* sliceDetails, GlobalNamespace::IScoreController* controller, GlobalNamespace::ColorScheme* colorScheme);

    public:
    SliceDetails::SliceDetailsFloatingScreen* sliceDetails;
    GlobalNamespace::ScoreController* scoreController;

    private:
    void HandleSwingFinish(GlobalNamespace::CutScoreBuffer* buffer);
    DelegateUtils::DelegateW<System::Action_1<GlobalNamespace::ScoringElement*>> onFinishDelegate;
)

#undef INTERFACES
