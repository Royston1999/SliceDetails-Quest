#include "UI/GridDotsViewController.hpp"
#include "bsml/shared/BSML.hpp"
#include "UnityEngine/UI/HorizontalLayoutGroup.hpp"
#include "assets.hpp"
#include "main.hpp"

DEFINE_TYPE(SliceDetails, GridDotsViewController);

namespace SliceDetails
{
    void GridDotsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (!firstActivation) return;
        BSML::parse_and_construct(IncludedAssets::GridDotsScreen_bsml, get_transform(), this);
        auto images = get_transform()->GetComponentsInChildren<HMUI::ImageView*>();
        std::copy(images.begin(), images.end(), gridDots);
    }
}