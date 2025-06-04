#pragma once

#include "UnityEngine/EventSystems/IPointerEnterHandler.hpp"
#include "UnityEngine/EventSystems/IPointerExitHandler.hpp"
#include "UnityEngine/EventSystems/IPointerClickHandler.hpp"
#include "UnityEngine/EventSystems/IEventSystemHandler.hpp"
#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include <functional>
#include "HMUI/ImageView.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UI/PanelUI.hpp"
#include "UI/SliceDetailsFloatingScreen.hpp"
#include "GlobalNamespace/HapticFeedbackManager.hpp"
#include "Libraries/HM/HMLib/VR/HapticPresetSO.hpp"
#include "GlobalNamespace/Signal.hpp"

#define INTERFACES \
    UnityEngine::EventSystems::IPointerEnterHandler*, UnityEngine::EventSystems::IPointerClickHandler*, \
    UnityEngine::EventSystems::IPointerExitHandler*, UnityEngine::EventSystems::IEventSystemHandler*

DECLARE_CLASS_CODEGEN_INTERFACES(SliceDetails, PanelUIHelper, UnityEngine::MonoBehaviour, INTERFACES) {

    DECLARE_OVERRIDE_METHOD_MATCH(void, OnPointerEnter, &::UnityEngine::EventSystems::IPointerEnterHandler::OnPointerEnter);
    DECLARE_OVERRIDE_METHOD_MATCH(void, OnPointerClick, &::UnityEngine::EventSystems::IPointerClickHandler::OnPointerClick);
    DECLARE_OVERRIDE_METHOD_MATCH(void, OnPointerExit, &::UnityEngine::EventSystems::IPointerExitHandler::OnPointerExit);

    public:
    static PanelUIHelper* AddPanelHelper(SliceDetailsFloatingScreen* screen, PanelUI* panelUI);
    private:
    PanelUI* panel;
    SliceDetailsFloatingScreen* sliceDetails;
    GlobalNamespace::Signal* buttonClickedSignal;
    void Vibrate(bool left);
    void UnFuckModal();
};

#undef INTERFACES