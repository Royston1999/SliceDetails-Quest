#include "UI/StatsPanel.hpp"
#include "bsml/shared/BSML.hpp"
#include "assets.hpp"
#include "UnityEngine/Canvas.hpp"
#include "UnityEngine/AdditionalCanvasShaderChannels.hpp"
#include "bsml/shared/Helpers/utilities.hpp"
#include "bsml/shared/Helpers/getters.hpp"
#include "bsml/shared/Helpers/creation.hpp"
#include "main.hpp"

DEFINE_TYPE(SliceDetails, StatsPanel);

using namespace UnityEngine;

namespace SliceDetails
{
    void StatsPanel::ActivatePanel(UnityEngine::Transform* transform, UnityEngine::Vector3 position, std::string text)
    {
        border->get_transform()->SetParent(transform, false);
        border->get_transform()->set_localPosition(transform->InverseTransformPoint(position) + Vector3(0.0f, 15.5f, 0.0f));
        this->text->SetText(text);
        border->get_gameObject()->set_active(true);
    }

    void StatsPanel::DeactivatePanel()
    {
        border->get_gameObject()->set_active(false);
    }

    void StatsPanel::PostParse()
    {
        auto cv = border->get_gameObject()->AddComponent<Canvas*>();
        cv->set_additionalShaderChannels(3);
        border->get_transform()->set_localScale({0.3f, 0.23f, 0.0f});
    }

    void StatsPanel::InitialiseUI(UnityEngine::Transform* parent)
    {
        // am i forgiven?
        BSML::parse_and_construct(IncludedAssets::StatsPanel_bsml, parent, this);
        DeactivatePanel();
    }
}