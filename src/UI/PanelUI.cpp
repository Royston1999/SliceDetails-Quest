#include "UI/PanelUI.hpp"
#include "bsml/shared/Helpers/getters.hpp"
#include "main.hpp"

DEFINE_TYPE(SliceDetails, PanelUI);

namespace SliceDetails
{
    void PanelUI::ctor(int index)
    {
        this->index = index;
    }

    void PanelUI::PostParse()
    {
        if (collider) return;
        collider = panelLayout->get_gameObject()->AddComponent<UnityEngine::BoxCollider*>();
        collider->set_size({9, 9, 0});
        background->set_material(BSML::Helpers::GetUINoGlowMat());
    }
}
