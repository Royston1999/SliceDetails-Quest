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
#include "GlobalNamespace/HapticFeedbackController.hpp"
#include "Libraries/HM/HMLib/VR/HapticPresetSO.hpp"
#include "GlobalNamespace/Signal.hpp"

#define INTERFACES \
    { \
        classof(UnityEngine::EventSystems::IPointerEnterHandler*), classof(UnityEngine::EventSystems::IPointerClickHandler*), \
        classof(UnityEngine::EventSystems::IPointerExitHandler*), classof(UnityEngine::EventSystems::IEventSystemHandler*) \
    } \

DECLARE_CLASS_CODEGEN_INTERFACES(SliceDetails, PanelUIHelper, UnityEngine::MonoBehaviour, std::vector<Il2CppClass*>(INTERFACES),

    DECLARE_OVERRIDE_METHOD(void, OnPointerEnter, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::UnityEngine::EventSystems::IPointerEnterHandler::OnPointerEnter>::get());
    DECLARE_OVERRIDE_METHOD(void, OnPointerClick, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::UnityEngine::EventSystems::IPointerClickHandler::OnPointerClick>::get());
    DECLARE_OVERRIDE_METHOD(void, OnPointerExit, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::UnityEngine::EventSystems::IPointerExitHandler::OnPointerExit>::get());

    public:
    static PanelUIHelper* AddPanelHelper(SliceDetailsFloatingScreen* screen, PanelUI* panelUI);
    private:
    PanelUI* panel;
    SliceDetailsFloatingScreen* sliceDetails;
    GlobalNamespace::Signal* buttonClickedSignal;
    void Vibrate(bool left);
)

#undef INTERFACES