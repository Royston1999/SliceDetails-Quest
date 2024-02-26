#include "UI/NoteUI.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "bsml/shared/Helpers/getters.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/FilterMode.hpp"
#include "bsml/shared/Helpers/utilities.hpp"
#include "main.hpp"
#include "UnityEngine/Canvas.hpp"
#include "UnityEngine/AdditionalCanvasShaderChannels.hpp"
#include "assets.hpp"

DEFINE_TYPE(SliceDetails, NoteUI)

namespace SliceDetails
{
    using namespace UnityEngine;

    void NoteUI::ctor(int rotation, int index)
    {
        rot = rotation;
        this->index = index;
    }

    Sprite* getArrowSprite() {
        static SafePtrUnity<Sprite> arrowSprite;
        if (!arrowSprite) {
            getLogger().debug("Creating Arrow Sprite");
            arrowSprite = BSML::Utilities::LoadSpriteRaw(IncludedAssets::arrow_png);
        }
        return arrowSprite.ptr();
    }

    Sprite* getDotSprite() {
        static SafePtrUnity<Sprite> dotSprite;
        if (!dotSprite) {
            getLogger().debug("Creating Dot Sprite");
            dotSprite = BSML::Utilities::LoadSpriteRaw(IncludedAssets::dot_png);
        }
        return dotSprite.ptr();
    }

    Sprite* getCutImageSprite() {
        static SafePtrUnity<Sprite> cutImageSprite;
        if (!cutImageSprite) {
            getLogger().debug("Creating Cut Image Sprite");
            Texture2D* texture = Texture2D::New_ctor(2, 2);
            texture->set_filterMode(FilterMode::Point);
            texture->Apply();
            cutImageSprite = BSML::Utilities::LoadSpriteFromTexture(texture);
        }
        return cutImageSprite.ptr();
    }

    void NoteUI::PostParse()
    {
        bloqLayout->get_transform()->set_rotation(Quaternion::Euler({0, 0, (float)rot}));
        bloqLayout->get_transform()->set_localScale({0.46f, 0.46f, 0.0f});
        bloqLayout->set_layer(5);
        Canvas* cv = bloqLayout->AddComponent<Canvas*>();
        cv->set_additionalShaderChannels(AdditionalCanvasShaderChannels::TexCoord1 | AdditionalCanvasShaderChannels::TexCoord2);
        cv->set_sortingOrder(4);

        noteArrow->set_sprite(index % 9 == 4 ? getDotSprite() : getArrowSprite());

        noteBackground->set_material(BSML::Helpers::GetUINoGlowMat());
        noteArrow->set_material(BSML::Helpers::GetUINoGlowMat());
        cutDistanceImage->set_material(BSML::Helpers::GetUINoGlowMat());
        noteCutArrow->set_material(BSML::Helpers::GetUINoGlowMat());

        noteBackground->get_transform()->set_localScale({4.0f, 4.0f, 0.0f});
        noteArrow->get_transform()->set_localScale({4.0f, 4.0f, 0.0f});
        cutDistanceImage->get_transform()->set_localScale({4.0f, 4.0f, 0.0f});
        noteCutArrow->get_transform()->set_localScale({4.0f, 4.0f, 0.0f});

        cutDistanceImage->set_sprite(getCutImageSprite());
        cutDistanceImage->set_color(Color(0.0f, 1.0f, 0.0f, 0.94f));

        if (!collider) collider = bloqLayout->get_gameObject()->AddComponent<BoxCollider*>();
        collider->set_size({14, 14, 0});
    }
}