#pragma once

#include <cmath>
#define _USE_MATH_DEFINES
#include "Data/GridInfo.hpp"
#include "Data/NoteInfo.hpp"
#include "UI/NoteUI.hpp"
#include "HMUI/ModalView.hpp"
#include "UI/PanelUI.hpp"
#include "questui/shared/CustomTypes/Components/FloatingScreen/FloatingScreenMoverPointer.hpp"
#include "questui/shared/CustomTypes/Components/Backgroundable.hpp"
#include "GlobalNamespace/SharedCoroutineStarter.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UI/HoverClickHelper.hpp"
#include "HMUI/Screen.hpp"
#include "UI/ModalHelper.hpp"

using namespace UnityEngine::UI;

namespace SliceDetails{
    class SliceDetailsUI{
        public:
            custom_types::Helpers::Coroutine createGridDots(HorizontalLayoutGroup* line1, HorizontalLayoutGroup* line2, HorizontalLayoutGroup* line3);
            custom_types::Helpers::Coroutine createNotes(HorizontalLayoutGroup* leftLine1, HorizontalLayoutGroup* leftLine2, HorizontalLayoutGroup* leftLine3, HorizontalLayoutGroup* rightLine1, HorizontalLayoutGroup* rightLine2, HorizontalLayoutGroup* rightLine3);
            custom_types::Helpers::Coroutine createPanelNotes(HorizontalLayoutGroup* line1, HorizontalLayoutGroup* line2, HorizontalLayoutGroup* line3);
            void createGridIndicator(UnityEngine::Transform* parent);
            void createModalUI(UnityEngine::Transform* parent);
            void createStatsPanel();
            void updateGridNotesInfo(int index);
            void updatePanelImages();
            void initScreen();
            void initNoteData();
            void refreshNoteData();
            void onPause();
            void onUnPause();
            void onResultsScreenActivate();
            void onResultsScreenDeactivate();
            void updateCoordinates(UnityEngine::Transform* transform);
            SliceDetails::NoteUI* modalNotes[18];
            SliceDetails::GridInfo* gridNotes[12];
            UnityEngine::UI::Image* gridDots[12];
            SliceDetails::PanelUI* panelImages[12];
            UnityEngine::UI::Image* hoverStatsPanel;
            UnityEngine::Color leftHand;
            UnityEngine::Color rightHand;
            UnityEngine::GameObject* screenhandle = nullptr;
            UnityEngine::GameObject* UIScreen = nullptr;
            HMUI::ModalView* modal = nullptr;
            UnityEngine::Material* UINoGlow = nullptr;
            bool isPaused = false;
            SliceDetails::HoverClickHelper* hoverClickHelper = nullptr;
            SliceDetails::ModalHelper* modalHelper = nullptr;
    };
}