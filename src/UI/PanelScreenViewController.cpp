#include "UI/PanelScreenViewController.hpp"
#include "bsml/shared/BSML.hpp"
#include "assets.hpp"
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"

DEFINE_TYPE(SliceDetails, PanelScreenViewController);

namespace SliceDetails
{
    void PanelScreenViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (!firstActivation) return;
        BSML::parse_and_construct(IncludedAssets::PanelScreen_bsml, get_transform(), this);
        auto layouts = get_transform()->GetComponentsInChildren<UnityEngine::UI::HorizontalLayoutGroup*>();
        for (int i = 0; i < 12; i++)
        {
            auto* layout = i<4 ? layouts[0] : i<8 ? layouts[1] : i<12 ? layouts[2] : nullptr;
            panelImages[i] = PanelUI::New_ctor(i);
            BSML::parse_and_construct(IncludedAssets::GridInfoUI_bsml, layout->get_transform(), panelImages[i]);
        }
        noteUIModal->InitialiseUI(get_transform());
    }
}