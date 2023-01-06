#pragma once
#include "custom-types/shared/macros.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Vector2.hpp"
#include "UnityEngine/Vector3.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "UnityEngine/PrimitiveType.hpp"
#include "UnityEngine/Transform.hpp"
#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/RectTransform.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Shader.hpp"
#include "UnityEngine/MeshRenderer.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/Resources.hpp"
#include "UnityEngine/RaycastHit.hpp"
#include "HMUI/ImageView.hpp"
#include "TMPro/TextMeshProUGUI.hpp"
#include "GlobalNamespace/VRController.hpp"
#include "VRUIControls/VRPointer.hpp"
#include "UnityEngine/Sprite.hpp"
#include "UnityEngine/Canvas.hpp"
#include "SliceDetailsConfig.hpp"
#include "Resources/Sprites.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "UnityEngine/RenderMode.hpp"
#include "UnityEngine/BoxCollider.hpp"
#include "UnityEngine/Collider2D.hpp"
#include "HMUI/HoverHintController.hpp"
#include "HMUI/HoverHintPanel.hpp"
#include "UnityEngine/RaycastHit.hpp"
#include "UnityEngine/Physics.hpp"

namespace SliceDetails{
    class PanelUI{
        public:
            TMPro::TextMeshProUGUI* text;
            UnityEngine::UI::Image* image;
            std::string hoverText;
            int index;
            PanelUI(UnityEngine::Transform* parent, UnityEngine::Sprite* image, int index);
            void set_panelText(std::string string);
    };
}