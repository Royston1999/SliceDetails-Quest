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
        border->get_transform()->set_localPosition(transform->InverseTransformPoint(position) + UnityEngine::Vector3(0.0f, 15.5f, 0.0f));
        this->text->SetText(text);
        border->get_gameObject()->set_active(true);
    }

    void StatsPanel::DeactivatePanel()
    {
        border->get_gameObject()->set_active(false);
    }

    void StatsPanel::InitialiseUI(UnityEngine::Transform* parent)
    {
        // BSML::parse_and_construct(IncludedAssets::StatsPanel_bsml, parent, this);
        // forgive me please i'll figure this shit out another time
        auto sprite = BSML::Utilities::LoadSpriteRaw(IncludedAssets::border_png);
        auto* GO = UnityEngine::GameObject::New_ctor("SliceDetailsStatsPanel");
        auto cv = GO->AddComponent<Canvas*>();
        cv->set_additionalShaderChannels(AdditionalCanvasShaderChannels::TexCoord1 | AdditionalCanvasShaderChannels::TexCoord2);
        cv->set_sortingOrder(4);
        border = GO->AddComponent<HMUI::ImageView*>();
        border->set_material(BSML::Helpers::GetUINoGlowMat());
        border->set_sprite(sprite);

        UnityEngine::RectTransform* rectTransform = (UnityEngine::RectTransform*)border->get_transform();
        rectTransform->set_anchorMin(UnityEngine::Vector2(0.5f, 0.5f));
        rectTransform->set_anchorMax(UnityEngine::Vector2(0.5f, 0.5f));
        rectTransform->set_anchoredPosition({0.0f, 0.0f});
        rectTransform->set_localScale({0.3f, 0.23f, 0.0f});
        // text = border->get_gameObject()->AddComponent<TMPro::TextMeshProUGUI*>();
        text = BSML::Helpers::CreateText(rectTransform, "", {0, 0});
        text->set_color(UnityEngine::Color::get_black());
        text->set_fontSize(10.0f);
        text->set_alignment(TMPro::TextAlignmentOptions::Center);
        border->get_gameObject()->set_active(false);
        GO->set_layer(4);
        border->get_transform()->SetParent(parent, false);
        DeactivatePanel();
    }
}