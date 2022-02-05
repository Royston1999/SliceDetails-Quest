#include "UI/ClickableImage.hpp"
#include "main.hpp"

DEFINE_TYPE(SliceDetails, ClickableImage);
void SliceDetails::ClickableImage::Awake(){
}
void SliceDetails::ClickableImage::Update(){
}

void SliceDetails::ClickableImage::set_text(std::string string){
    text->GetComponentInChildren<TMPro::TextMeshProUGUI*>()->set_text(il2cpp_utils::createcsstr(string));
}

namespace SliceDetails{
    SliceDetails::ClickableImage* CreateClickableImage(UnityEngine::Transform* parent, std::string name, UnityEngine::Sprite* sprite, std::string text, int index){
        UnityEngine::GameObject* mainCanvas = QuestUI::BeatSaberUI::CreateCanvas();
        mainCanvas->set_active(false);
        SliceDetails::ClickableImage* clickimg = mainCanvas->AddComponent<SliceDetails::ClickableImage*>();
        clickimg->modalComponent = false;
        clickimg->index = index;
        clickimg->image = QuestUI::BeatSaberUI::CreateCanvas();
        UnityEngine::UI::Image* theimg = clickimg->image->AddComponent<UnityEngine::UI::Image*>();
        theimg->set_material(SliceDetails::Main::SliceDetailsUI->UINoGlow);
        theimg->set_sprite(sprite);

        clickimg->text = UnityEngine::GameObject::New_ctor(il2cpp_utils::createcsstr("text"), UnityEngine::Canvas::New_ctor()->GetType());
        TMPro::TextMeshProUGUI* thetext = clickimg->text->AddComponent<TMPro::TextMeshProUGUI*>();
        thetext->set_text(il2cpp_utils::createcsstr(text));
        thetext->get_gameObject()->set_layer(1);
        thetext->set_isOverlay(true);
        thetext->set_fontSize(5.0f);
        thetext->set_alignment(TMPro::TextAlignmentOptions::Center);

        clickimg->hoverHint = UnityEngine::GameObject::New_ctor(il2cpp_utils::createcsstr("hint"), UnityEngine::Canvas::New_ctor()->GetType());
        auto* collider = clickimg->hoverHint->AddComponent<UnityEngine::BoxCollider*>();
        collider->set_size({13.0f, 13.0f, 0.0f});
        collider->set_name(il2cpp_utils::createcsstr("gridcollider"));
        clickimg->theHint = QuestUI::BeatSaberUI::AddHoverHint(collider->get_gameObject(), "knob knob fat cunt " + text);
        clickimg->theHint->hoverHintController = nullptr;

        UnityEngine::RectTransform* rectTransform = (UnityEngine::RectTransform*)theimg->get_transform();
        rectTransform->set_anchorMin(UnityEngine::Vector2(0.5f, 0.5f));
        rectTransform->set_anchorMax(UnityEngine::Vector2(0.5f, 0.5f));
        rectTransform->set_anchoredPosition({0.0f, 0.0f});
        rectTransform->set_sizeDelta({4, 4});
        rectTransform->set_localScale({4.0f, 4.0f, 0.0f});
        theimg->set_color(UnityEngine::Color::get_gray());

        mainCanvas->get_transform()->set_localScale({0.57f, 0.57f, 0.0f});
        rectTransform->SetParent(mainCanvas->get_transform(), false);
        thetext->get_transform()->SetParent(mainCanvas->get_transform(), false);
        collider->get_transform()->SetParent(mainCanvas->get_transform(), false);
        clickimg->theHint->get_transform()->SetParent(mainCanvas->get_transform(), true);
        mainCanvas->get_transform()->SetParent(parent, false);

        clickimg->theHint->set_enabled(true);
        mainCanvas->set_active(true);

        return clickimg;
    }
}