#include "Utils/HandleHighlighter.hpp"
#include "main.hpp"
#include "UnityEngine/Shader.hpp"

DEFINE_TYPE(SliceDetails, HandleHighlighter);

namespace SliceDetails
{

    void HandleHighlighter::Start()
    {
        renderer = GetComponent<UnityEngine::MeshRenderer*>();
        origMat = renderer->get_material();
        hoveringHandle = false;
        floater->grabbingHandle = false;
    }

    void HandleHighlighter::OnPointerUp()
    {
        floater->grabbingHandle = false;
        if (hoveringHandle) return;
        renderer->set_material(origMat);
    }

    void HandleHighlighter::OnPointerEnter()
    {
        hoveringHandle = true;
        renderer->set_material(GetHoverMat());
    }

    void HandleHighlighter::OnPointerDown()
    {
        floater->grabbingHandle = true;
        renderer->set_material(GetHoverMat());
    }

    void HandleHighlighter::OnPointerExit()
    {
        hoveringHandle = false;
        if (floater->grabbingHandle) return;
        renderer->set_material(origMat);
    }

    HandleHighlighter* HandleHighlighter::AddHighlight(SliceDetailsFloatingScreen* screen, UnityEngine::GameObject* handle)
    {
        auto highlight = handle->AddComponent<HandleHighlighter*>();
        highlight->floater = screen;
        return highlight;
    }

    
    UnityEngine::Material* HandleHighlighter::GetHoverMat() {
        static SafePtrUnity<UnityEngine::Material> hoverMaterial;
        if (!hoverMaterial) {
            auto shader = UnityEngine::Shader::Find("Hidden/Internal-DepthNormalsTexture");
            hoverMaterial = UnityEngine::Material::New_ctor(shader);
        }
        return hoverMaterial.ptr();
    }

}