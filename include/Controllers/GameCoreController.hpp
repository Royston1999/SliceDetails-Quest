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
#include "System/IDisposable.hpp"
#include "Zenject/IInitializable.hpp"

#define INTERFACES System::IDisposable*, Zenject::IInitializable* 

DECLARE_CLASS_CODEGEN_INTERFACES(SliceDetails, GameCoreController, Il2CppObject, INTERFACES) {
    
    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &::Zenject::IInitializable::Initialize);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &::System::IDisposable::Dispose);
    
    DECLARE_CTOR(ctor, SliceDetails::SliceDetailsFloatingScreen* sliceDetails, GlobalNamespace::IScoreController* controller, GlobalNamespace::ColorScheme* colorScheme);

    public:
    SliceDetails::SliceDetailsFloatingScreen* sliceDetails;
    GlobalNamespace::ScoreController* scoreController;

    private:
    void HandleSwingFinish(GlobalNamespace::CutScoreBuffer* buffer);
    void OnScoreFinish(GlobalNamespace::ScoringElement* scoringElement);
};

#undef INTERFACES
