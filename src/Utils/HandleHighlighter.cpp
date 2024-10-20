#include "Utils/HandleHighlighter.hpp"
#include "main.hpp"
#include "UnityEngine/Shader.hpp"

DEFINE_TYPE(SliceDetails, HandleHighlighter);

namespace SliceDetails
{
    void HandleHighlighter::Start()
    {
        hoveringHandle = false;
        floater->grabbingHandle = false;
    }

    void HandleHighlighter::OnPointerUp()
    {
        floater->grabbingHandle = false;
    }

    void HandleHighlighter::OnPointerEnter()
    {
        hoveringHandle = true;
    }

    void HandleHighlighter::OnPointerDown()
    {
        floater->grabbingHandle = true;
    }

    void HandleHighlighter::OnPointerExit()
    {
        hoveringHandle = false;
    }

    HandleHighlighter* HandleHighlighter::AddHighlight(SliceDetailsFloatingScreen* screen, UnityEngine::GameObject* handle)
    {
        auto highlight = handle->AddComponent<HandleHighlighter*>();
        highlight->floater = screen;
        return highlight;
    }
}