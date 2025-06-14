#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "bsml/shared/macros.hpp"
#include "bsml/shared/BSML/FloatingScreen/FloatingScreen.hpp"
#include "bsml/shared/BSML/FloatingScreen/FloatingScreenHandleEventArgs.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UI/PanelScreenViewController.hpp"
#include "Data/GridInfo.hpp"
#include "UnityEngine/Color.hpp"
#include "UI/NoteUIModal.hpp"
#include "UI/StatsPanel.hpp"
#include "System/IDisposable.hpp"
#include "Zenject/IInitializable.hpp"

#define INTERFACES System::IDisposable*, Zenject::IInitializable*

DECLARE_CLASS_CODEGEN_INTERFACES(SliceDetails, SliceDetailsFloatingScreen, Il2CppObject, INTERFACES) {
    
    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &::Zenject::IInitializable::Initialize);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Dispose, &::System::IDisposable::Dispose);
    
    DECLARE_CTOR(ctor, PanelScreenViewController* psvc, NoteUIModal* modal, StatsPanel* statsPanel);

    DECLARE_INSTANCE_METHOD(void, OnPause);
    DECLARE_INSTANCE_METHOD(void, OnUnPause);
    DECLARE_INSTANCE_METHOD(void, OnResultsScreenActivate);
    DECLARE_INSTANCE_METHOD(void, OnResultsScreenDeactivate);
    DECLARE_INSTANCE_METHOD(void, ClearNoteData);
    DECLARE_INSTANCE_METHOD(void, InitialiseUI);
    DECLARE_INSTANCE_METHOD(void, UpdatePanelScreen);
    DECLARE_INSTANCE_METHOD(void, UpdateNoteInfoUI, int index);
    DECLARE_INSTANCE_METHOD(bool, IsEnabled);
    DECLARE_INSTANCE_METHOD(bool, DisplayInPause);
    DECLARE_INSTANCE_METHOD(bool, DisplayInResults);

    public:
    void UpdateCoordinates(BSML::FloatingScreen* self, const BSML::FloatingScreenHandleEventArgs& args);
    SliceDetails::GridInfo* gridNotes[12];
    SliceDetails::PanelScreenViewController* panelScreen;
    UnityEngine::UI::Image* hoverStatsPanel;
    UnityEngine::Color leftHand;
    UnityEngine::Color rightHand;
    UnityEngine::GameObject* screenhandle = nullptr;
    BSML::FloatingScreen* floatingScreen = nullptr;
    StatsPanel* statsPanel = nullptr;
    bool isPaused = false;
    bool isInitialised = false;
    bool grabbingHandle = false;
};

#undef INTERFACES
