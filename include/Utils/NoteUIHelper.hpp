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
    UnityEngine::EventSystems::IPointerEnterHandler*, \
    UnityEngine::EventSystems::IPointerExitHandler*, UnityEngine::EventSystems::IEventSystemHandler*

DECLARE_CLASS_CODEGEN_INTERFACES(SliceDetails, NoteUIHelper, UnityEngine::MonoBehaviour, INTERFACES) {

    DECLARE_OVERRIDE_METHOD_MATCH(void, OnPointerEnter, &::UnityEngine::EventSystems::IPointerEnterHandler::OnPointerEnter);
    DECLARE_OVERRIDE_METHOD_MATCH(void, OnPointerExit, &::UnityEngine::EventSystems::IPointerExitHandler::OnPointerExit);

    public:
    static NoteUIHelper* AddNoteHelper(SliceDetailsFloatingScreen* screen, NoteUI* noteUI);
    private:
    NoteUI* note;
    SliceDetailsFloatingScreen* sliceDetails;
};

#undef INTERFACES