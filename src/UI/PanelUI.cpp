#include "UI/PanelUI.hpp"
#include "main.hpp"

void SliceDetails::PanelUI::set_panelText(std::string string){
    text->set_text(il2cpp_utils::createcsstr(string));
}

SliceDetails::PanelUI::PanelUI(UnityEngine::Transform* parent, UnityEngine::Sprite* sprite, int index){
    UnityEngine::GameObject* mainCanvas = QuestUI::BeatSaberUI::CreateCanvas();
    mainCanvas->set_active(false);
    this->index = index;
    image = QuestUI::BeatSaberUI::CreateCanvas()->AddComponent<UnityEngine::UI::Image*>();
    image->set_material(SliceDetails::Main::SliceDetailsUI->UINoGlow);
    image->set_sprite(sprite);

    text = UnityEngine::GameObject::New_ctor(il2cpp_utils::createcsstr("text"))->AddComponent<TMPro::TextMeshProUGUI*>();
    text->get_gameObject()->set_layer(1);
    text->set_isOverlay(true);
    text->set_fontSize(5.0f);
    text->set_alignment(TMPro::TextAlignmentOptions::Center);

    auto* collider = mainCanvas->AddComponent<UnityEngine::BoxCollider*>();
    hoverHint = QuestUI::BeatSaberUI::AddHoverHint(collider->get_gameObject(), "knob knob fat cunt");
    collider->set_size({13.0f, 13.0f, 0.0f});
    collider->set_name(il2cpp_utils::createcsstr("gridcollider " + std::to_string(index)));
    hoverHint->hoverHintController = nullptr;

    UnityEngine::RectTransform* rectTransform = (UnityEngine::RectTransform*)image->get_transform();
    rectTransform->set_anchorMin(UnityEngine::Vector2(0.5f, 0.5f));
    rectTransform->set_anchorMax(UnityEngine::Vector2(0.5f, 0.5f));
    rectTransform->set_anchoredPosition({0.0f, 0.0f});
    rectTransform->set_sizeDelta({4, 4});
    rectTransform->set_localScale({4.0f, 4.0f, 0.0f});
    image->set_color(UnityEngine::Color::get_gray());

    mainCanvas->get_transform()->set_localScale({0.57f, 0.57f, 0.0f});
    rectTransform->SetParent(mainCanvas->get_transform(), false);
    text->get_transform()->SetParent(mainCanvas->get_transform(), false);
    collider->get_transform()->SetParent(mainCanvas->get_transform(), false);
    hoverHint->get_transform()->SetParent(mainCanvas->get_transform(), true);
    mainCanvas->get_transform()->SetParent(parent, false);

    hoverHint->set_enabled(true);
    mainCanvas->set_active(true);
}
