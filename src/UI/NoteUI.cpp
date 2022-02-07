#include "UI/NoteUI.hpp"
#include "main.hpp"

UnityEngine::UI::Image* createImage(UnityEngine::UI::Image* img, UnityEngine::Sprite* sprite, UnityEngine::Transform* parent){
    auto* GO = QuestUI::BeatSaberUI::CreateCanvas();
    img = GO->AddComponent<UnityEngine::UI::Image*>();
    img->set_material(SliceDetails::Main::SliceDetailsUI->UINoGlow);
    img->set_sprite(sprite);

    UnityEngine::RectTransform* rectTransform = (UnityEngine::RectTransform*)img->get_transform();
    rectTransform->set_anchorMin(UnityEngine::Vector2(0.5f, 0.5f));
    rectTransform->set_anchorMax(UnityEngine::Vector2(0.5f, 0.5f));
    rectTransform->set_anchoredPosition({0.0f, 0.0f});
    rectTransform->set_sizeDelta({4, 4});
    rectTransform->set_localScale({4.0f, 4.0f, 0.0f});
    rectTransform->SetParent(parent, false);
    return img;
}

UnityEngine::UI::Image* createTexture(UnityEngine::UI::Image* img, UnityEngine::Transform* parent){
    auto* GO = QuestUI::BeatSaberUI::CreateCanvas();
    img = GO->AddComponent<UnityEngine::UI::Image*>();
    UnityEngine::Texture2D* texture = UnityEngine::Texture2D::New_ctor(2, 2);
    texture->set_filterMode(UnityEngine::FilterMode::Point);
    texture->Apply();
    img->set_material(SliceDetails::Main::SliceDetailsUI->UINoGlow);
	img->set_sprite(UnityEngine::Sprite::Create(texture, UnityEngine::Rect(0, 0, texture->get_width(), texture->get_height()), UnityEngine::Vector2(0, 0), 100.0f, 1u, UnityEngine::SpriteMeshType::FullRect, UnityEngine::Vector4(0.0f, 0.0f, 0.0f, 0.0f), false));
    
    UnityEngine::RectTransform* rectTransform = (UnityEngine::RectTransform*)img->get_transform();
    rectTransform->set_anchorMin(UnityEngine::Vector2(0.5f, 0.5f));
    rectTransform->set_anchorMax(UnityEngine::Vector2(0.5f, 0.5f));
    rectTransform->set_anchoredPosition({0.0f, 0.0f});
    rectTransform->set_sizeDelta({4, 4});
    rectTransform->set_localScale({4.0f, 4.0f, 0.0f});
    rectTransform->SetParent(parent, false);
    img->set_color(UnityEngine::Color(0.0f, 1.0f, 0.0f, 0.94f));
    return img;
}

SliceDetails::NoteUI::NoteUI(UnityEngine::Transform* parent, UnityEngine::Sprite* noteArrowSprite, int rotation){
    rot = rotation;
    auto* transform = QuestUI::BeatSaberUI::CreateCanvas()->get_transform();
    transform->set_localScale({0.46f, 0.46f, 0.0f});
    noteBackground = createImage(noteBackground, QuestUI::BeatSaberUI::Base64ToSprite(SliceDetails::Sprites::bloq), transform);
    noteArrow = createImage(noteArrow, noteArrowSprite, transform);
    cutDistanceImage = createTexture(cutDistanceImage, transform);
    noteCutArrow = createImage(noteCutArrow, QuestUI::BeatSaberUI::Base64ToSprite(SliceDetails::Sprites::cut_arrow), transform);
    collider = UnityEngine::GameObject::New_ctor()->AddComponent<UnityEngine::Canvas*>()->get_gameObject()->AddComponent<UnityEngine::BoxCollider*>();
    collider->set_size({12.0f, 12.0f, 0.0f});
    collider->set_name(il2cpp_utils::createcsstr("modalcollider"));
    hint = QuestUI::BeatSaberUI::AddHoverHint(collider->get_gameObject(), std::to_string(rotation) + " KNOB");
    hint->hoverHintController = nullptr;
    hint->set_enabled(true);
    collider->get_transform()->SetParent(transform, false);
    hint->get_transform()->SetParent(transform, false);
    transform->set_rotation(UnityEngine::Quaternion::Euler(0, 0, rotation));
    transform->SetParent(parent, false);
}