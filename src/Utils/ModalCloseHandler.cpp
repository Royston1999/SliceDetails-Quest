#include "Utils/ModalCloseHandler.hpp"
#include "main.hpp"

DEFINE_TYPE(SliceDetails, ModalCloseHandler);

namespace SliceDetails
{

    void ModalCloseHandler::OnEnable()
    {
        justEnabled = true;
    }

    void ModalCloseHandler::FixedUpdate()
    {
        auto modal = sliceDetails->panelScreen->noteUIModal->modal;
        if (!modal->isShown) return;
        auto pointer = sliceDetails->floatingScreen->screenMover->_vrPointer;
        if (!pointer || !pointer->m_CachedPtr.m_value) return;
        auto controller = pointer->vrController;
        if (!controller || !controller->m_CachedPtr.m_value) return;
        if (controller->get_triggerValue() > 0.9f && !justEnabled && !sliceDetails->grabbingHandle && !high->hoveringHandle) modal->Hide(true, nullptr);
        else if (controller->get_triggerValue() < 0.35f) justEnabled = false;
    }

    ModalCloseHandler* ModalCloseHandler::AddModalCloser(HMUI::ModalView* modal, HandleHighlighter* highlight, SliceDetailsFloatingScreen* screen)
    {
        auto closer = modal->get_gameObject()->AddComponent<ModalCloseHandler*>();
        closer->sliceDetails = screen;
        closer->high = highlight;
        return closer;
    }
}