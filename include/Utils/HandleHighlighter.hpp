#pragma once

#include "UnityEngine/EventSystems/IPointerEnterHandler.hpp"
#include "UnityEngine/EventSystems/IPointerExitHandler.hpp"
#include "UnityEngine/EventSystems/IPointerClickHandler.hpp"
#include "UnityEngine/EventSystems/IEventSystemHandler.hpp"
#include "UnityEngine/EventSystems/IPointerDownHandler.hpp"
#include "UnityEngine/EventSystems/IPointerUpHandler.hpp"
#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include <functional>
#include "HMUI/ImageView.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UI/SliceDetailsFloatingScreen.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/MeshRenderer.hpp"

#define INTERFACES \
    UnityEngine::EventSystems::IPointerEnterHandler*, UnityEngine::EventSystems::IPointerDownHandler*, \
    UnityEngine::EventSystems::IPointerExitHandler*, UnityEngine::EventSystems::IPointerUpHandler*, \
    UnityEngine::EventSystems::IEventSystemHandler* 

DECLARE_CLASS_CODEGEN_INTERFACES(SliceDetails, HandleHighlighter, UnityEngine::MonoBehaviour, INTERFACES) {

    DECLARE_OVERRIDE_METHOD_MATCH(void, OnPointerEnter, &::UnityEngine::EventSystems::IPointerEnterHandler::OnPointerEnter);
    DECLARE_OVERRIDE_METHOD_MATCH(void, OnPointerDown, &::UnityEngine::EventSystems::IPointerDownHandler::OnPointerDown);
    DECLARE_OVERRIDE_METHOD_MATCH(void, OnPointerUp, &::UnityEngine::EventSystems::IPointerUpHandler::OnPointerUp);
    DECLARE_OVERRIDE_METHOD_MATCH(void, OnPointerExit, &::UnityEngine::EventSystems::IPointerExitHandler::OnPointerExit);
    DECLARE_INSTANCE_METHOD(void, Start);

    public:
    static HandleHighlighter* AddHighlight(SliceDetailsFloatingScreen* screen, UnityEngine::GameObject* handle);
    bool hoveringHandle = false;
    private:
    SliceDetailsFloatingScreen* floater;
};

#undef INTERFACES