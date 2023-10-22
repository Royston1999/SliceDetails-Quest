#include "UI/NoteUIModal.hpp"
#include "bsml/shared/BSML.hpp"
#include "assets.hpp"
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "UnityEngine/Quaternion.hpp"
#include "HMUI/ViewController_AnimationType.hpp"
#include "main.hpp"
#include "UnityEngine/UI/ContentSizeFitter.hpp"
#include "UnityEngine/Canvas.hpp"
#include "bsml/shared/BSML/Components/Backgroundable.hpp"

DEFINE_TYPE(SliceDetails, NoteUIModal);

namespace SliceDetails
{
    using namespace UnityEngine;
    using namespace UnityEngine::UI;

    void NoteUIModal::ctor(GridDotsViewController* dots)
    {   
        INVOKE_CTOR();
        gridDots = dots;
    }

    void NoteUIModal::PostParse()
    {
        modal->get_transform()->Translate({0.0f, 0.0f, -0.01f});
    }

    void NoteUIModal::InitialiseUI(UnityEngine::Transform* parent)
    {
        getLogger().debug("Creating Modal Screen");
        BSML::parse_and_construct(IncludedAssets::NoteUIModal_bsml, parent, this);
        
        auto layouts = modal->get_transform()->GetComponentsInChildren<UI::HorizontalLayoutGroup*>();
        int rots[9] = {225, 180, 135, 270, 0, 90, 315, 0, 45};
        for (int i = 0; i < 18; i++)
        {    
            auto* layout = layouts[(int)(i/3)+1];
            modalNotes[i] = NoteUI::New_ctor(rots[i%9], i);
            auto note = modalNotes[i]->bloqLayout = GameObject::New_ctor("SliceDetailsModalNote");
            note->get_transform()->SetParent(layout->get_transform(), false);
            BSML::parse_and_construct(IncludedAssets::NoteInfoUI_bsml, note->get_transform(), modalNotes[i]);
        }

        // this shouldn't really be a floating screen but nevermind
        auto gridDotsScreen = BSML::FloatingScreen::CreateFloatingScreen({12.0f, 8.0f}, false, {0.0f, 1.0f, 1.0f}, Quaternion::Euler({0, 0, 0}), 0, false);    
        auto canvas = gridDotsScreen->get_transform()->GetComponentInChildren<Canvas*>();
        canvas->set_sortingOrder(31);
        auto backgroundGo = GameObject::New_ctor("bg");
        backgroundGo->get_transform()->SetParent(canvas->get_transform(), false);
        auto background = backgroundGo->AddComponent<BSML::Backgroundable*>();
        background->ApplyBackground("round-rect-panel");
        background->ApplyAlpha(0.94f);
        
        gridDotsScreen->SetRootViewController(gridDots, HMUI::ViewController::AnimationType::None);
        gridDotsScreen->get_gameObject()->set_active(true);
        gridDotsScreen->rootViewController->__Activate(false, false);
        gridDotsScreen->get_transform()->SetParent(modal->get_transform(), false);
        gridDotsScreen->get_transform()->set_localPosition(gridDotsScreen->get_transform()->get_localPosition() + Vector3(0.0f, 15.0f, -1.2f));
        gridDotsScreen->get_transform()->set_localScale({0.85f, 0.85f, 0.0f});
    }
}