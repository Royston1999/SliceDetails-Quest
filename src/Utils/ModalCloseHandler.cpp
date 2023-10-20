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
        auto controller = sliceDetails->floatingScreen->screenMover->_vrPointer->vrController;
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