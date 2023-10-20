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
    { \
        classof(UnityEngine::EventSystems::IPointerEnterHandler*), classof(UnityEngine::EventSystems::IPointerDownHandler*), \
        classof(UnityEngine::EventSystems::IPointerExitHandler*), classof(UnityEngine::EventSystems::IPointerUpHandler*), \
        classof(UnityEngine::EventSystems::IEventSystemHandler*) \
    } \

DECLARE_CLASS_CODEGEN_INTERFACES(SliceDetails, HandleHighlighter, UnityEngine::MonoBehaviour, std::vector<Il2CppClass*>(INTERFACES),

    DECLARE_OVERRIDE_METHOD(void, OnPointerEnter, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::UnityEngine::EventSystems::IPointerEnterHandler::OnPointerEnter>::get());
    DECLARE_OVERRIDE_METHOD(void, OnPointerDown, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::UnityEngine::EventSystems::IPointerDownHandler::OnPointerDown>::get());
    DECLARE_OVERRIDE_METHOD(void, OnPointerUp, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::UnityEngine::EventSystems::IPointerUpHandler::OnPointerUp>::get());
    DECLARE_OVERRIDE_METHOD(void, OnPointerExit, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::UnityEngine::EventSystems::IPointerExitHandler::OnPointerExit>::get());
    DECLARE_INSTANCE_METHOD(void, Start);

    public:
    static HandleHighlighter* AddHighlight(SliceDetailsFloatingScreen* screen, UnityEngine::GameObject* handle);
    bool hoveringHandle = false;
    private:
    SliceDetailsFloatingScreen* floater;
    UnityEngine::MeshRenderer* renderer;
    UnityEngine::Material* origMat;
    UnityEngine::Material* GetHoverMat();
    
)

#undef INTERFACES