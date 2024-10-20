#include "Utils/NoteUIHelper.hpp"
#include "main.hpp"
#include "UnityEngine/Canvas.hpp"

DEFINE_TYPE(SliceDetails, NoteUIHelper);

namespace SliceDetails
{

    NoteUIHelper* NoteUIHelper::AddNoteHelper(SliceDetailsFloatingScreen* screen, NoteUI* noteUI)
    {
        auto helper = noteUI->collider->get_gameObject()->AddComponent<NoteUIHelper*>();
        helper->sliceDetails = screen;
        helper->note = noteUI;
        return helper;
    }

    void NoteUIHelper::OnPointerEnter()
    {
        if (note->hoverText.empty()) return;
        if (sliceDetails->grabbingHandle) return;
        sliceDetails->statsPanel->ActivatePanel(sliceDetails->panelScreen->noteUIModal->modal->get_transform(), note->collider->get_transform()->get_position(), note->hoverText);
    }

    void NoteUIHelper::OnPointerExit()
    {
        sliceDetails->statsPanel->DeactivatePanel();
    }

}