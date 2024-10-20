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
#include "UI/NoteUI.hpp"
#include "UI/SliceDetailsFloatingScreen.hpp"

#define INTERFACES \
    { \
        classof(UnityEngine::EventSystems::IPointerEnterHandler*), \
        classof(UnityEngine::EventSystems::IPointerExitHandler*), classof(UnityEngine::EventSystems::IEventSystemHandler*) \
    } \

DECLARE_CLASS_CODEGEN_INTERFACES(SliceDetails, NoteUIHelper, UnityEngine::MonoBehaviour, std::vector<Il2CppClass*>(INTERFACES),

    DECLARE_OVERRIDE_METHOD(void, OnPointerEnter, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::UnityEngine::EventSystems::IPointerEnterHandler::OnPointerEnter>::methodInfo());
    DECLARE_OVERRIDE_METHOD(void, OnPointerExit, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::UnityEngine::EventSystems::IPointerExitHandler::OnPointerExit>::methodInfo());

    public:
    static NoteUIHelper* AddNoteHelper(SliceDetailsFloatingScreen* screen, NoteUI* noteUI);
    private:
    NoteUI* note;
    SliceDetailsFloatingScreen* sliceDetails;
)

#undef INTERFACES