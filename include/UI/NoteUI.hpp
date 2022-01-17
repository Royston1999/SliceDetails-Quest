#pragma once
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/UI/Image.hpp"
#include "UnityEngine/Space.hpp"
#include "HMUI/HoverHint.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/Canvas.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "Resources/Sprites.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/BoxCollider.hpp"
#include "HMUI/HoverHintController.hpp"
#include "HMUI/HoverHintPanel.hpp"
#include "UnityEngine/Texture2D.hpp"
#include "UnityEngine/FilterMode.hpp"
#include "UnityEngine/Rect.hpp"
#include "UnityEngine/SpriteMeshType.hpp"
#include <iomanip>


namespace SliceDetails{
    class NoteUI{
        public:
            UnityEngine::UI::Image* noteBackground;
            UnityEngine::UI::Image* noteArrow;
            UnityEngine::UI::Image* noteCutArrow;
            UnityEngine::BoxCollider* collider; // might not be needed
            UnityEngine::UI::Image* cutDistanceImage;
            HMUI::HoverHint* hint;
            int rot;
            NoteUI(UnityEngine::Transform* parent, UnityEngine::Sprite* noteArrowSprite, int rotation);
    };
}