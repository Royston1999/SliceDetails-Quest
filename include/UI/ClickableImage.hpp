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

DECLARE_CLASS_CODEGEN(SliceDetails, ClickableImage, UnityEngine::MonoBehaviour,
    DECLARE_INSTANCE_METHOD(void, Awake);
    DECLARE_INSTANCE_METHOD(void, Update);

    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, text);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, image);
    DECLARE_INSTANCE_FIELD(UnityEngine::GameObject*, hoverHint);
    DECLARE_INSTANCE_FIELD(HMUI::HoverHint*, theHint);
    DECLARE_INSTANCE_FIELD(bool, modalComponent);
    DECLARE_INSTANCE_FIELD(int, index);

    public:
        void set_text(std::string string);
);

namespace SliceDetails{
    SliceDetails::ClickableImage* CreateClickableImage(UnityEngine::Transform* parent, std::string name, UnityEngine::Sprite* image, std::string text, int index);
}