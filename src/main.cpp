#include "main.hpp"
#include "SliceDetailsConfig.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"
#include "GlobalNamespace/StandardLevelDetailView.hpp"
#include "TMPro/TextMeshProUGUI.hpp"

#include "bsml/shared/BSMLDataCache.hpp"
#include "assets.hpp"
#include "lapiz/shared/zenject/Zenjector.hpp"
#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"
#include "Zenject/ConcreteIdBinderGeneric_1.hpp"
#include "UI/SliceDetailsFloatingScreen.hpp"
#include "bsml/shared/BSML.hpp"
#include "bsml/shared/BSML/Components/Settings/ToggleSetting.hpp"
#include "UnityEngine/UI/Toggle.hpp"
#include "UnityEngine/Events/UnityAction_1.hpp"
#include "lapiz/shared/utilities/ZenjectExtensions.hpp"
#include "Controllers/GameCoreController.hpp"
#include "Controllers/PauseController.hpp"
#include "Controllers/MenuController.hpp"
#include "UI/StatsPanel.hpp"
#include "GlobalNamespace/GameplayCoreInstaller.hpp"
#include "DelegateUtils.hpp"
#include "lapiz/shared/utilities/MainThreadScheduler.hpp"

using namespace UnityEngine;
using namespace GlobalNamespace;
using namespace SliceDetails;
using namespace UnityEngine::UI;
using namespace DelegateUtils;
using ToggleDelegate = UnityEngine::Events::UnityAction_1<bool>;

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

const Paper::ConstLoggerContext<13UL>& getLogger() {
    static constexpr auto Logger = Paper::ConstLoggerContext("slicedetails");
    return Logger;
}

SLICE_DETAILS_EXPORT_FUNC void setup(CModInfo& info) {
    info = modInfo.to_c();

    getLogger().info("Completed setup!");
}

#if !NO_GIMMICK
//ha ha funny skilly issue
MAKE_HOOK_MATCH(levelview, &StandardLevelDetailView::RefreshContent, void, StandardLevelDetailView* self) {
    levelview(self);
    auto* text = self->get_practiceButton()->get_transform()->GetComponentInChildren<TMPro::TextMeshProUGUI*>();
    std::thread([text](){ 
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        Lapiz::Utilities::MainThreadScheduler::Schedule([text]() {
            text->set_text("Skill Issue");
        });
    }).detach();
}
#endif

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool two, bool three)
{
    if (!firstActivation) return;
    BSML::parse_and_construct(IncludedAssets::SettingsUI_bsml, self->get_transform());
    auto toggles = self->get_transform()->GetComponentsInChildren<BSML::ToggleSetting*>();
    Toggle *pToggle = toggles[0]->toggle, *rToggle = toggles[1]->toggle;
    ToggleDelegate *pDel = nullptr, *rDel = nullptr;
    pDel += DelegateW<ToggleDelegate>([](bool value){getSliceDetailsConfig().inPause.SetValue(value);});
    rDel += DelegateW<ToggleDelegate>([](bool value){getSliceDetailsConfig().inResults.SetValue(value);});
    pToggle->___onValueChanged->AddListener(pDel);
    rToggle->___onValueChanged->AddListener(rDel);
    pToggle->set_isOn(getSliceDetailsConfig().inPause.GetValue());
    rToggle->set_isOn(getSliceDetailsConfig().inResults.GetValue());
}

SLICE_DETAILS_EXPORT_FUNC void late_load() {
    il2cpp_functions::Init();
    getSliceDetailsConfig().Init(modInfo);
    BSML::Init();
    custom_types::Register::AutoRegister();
    BSML::Register::RegisterSettingsMenu("Slice Details", &DidActivate, false);

#if !NO_GIMMICK
    INSTALL_HOOK(getLogger(), levelview);
#endif

    using namespace Lapiz::Zenject::ZenjectExtensions;
    using namespace Lapiz::Zenject;
    using namespace Zenject;

    auto zenjector = Zenjector::Get();

    zenjector->Install(Location::App, [](DiContainer* container)
    {
        container->BindInterfacesAndSelfTo<SliceDetailsFloatingScreen*>()->AsSingle()->NonLazy();
        container->Bind<NoteUIModal*>()->AsSingle();
        container->Bind<StatsPanel*>()->AsSingle();
        FromNewComponentAsViewController(container->Bind<PanelScreenViewController*>())->AsSingle();
        FromNewComponentAsViewController(container->Bind<GridDotsViewController*>())->AsSingle();
    });

    zenjector->Install<GameplayCoreInstaller*>([](DiContainer* container)
    {
        auto screen = container->Resolve<SliceDetailsFloatingScreen*>();
        if (!screen->IsEnabled()) return;
        container->BindInterfacesAndSelfTo<GameCoreController*>()->AsSingle();
    });

    zenjector->Install(Location::StandardPlayer, [](DiContainer* container)
    {
        auto screen = container->Resolve<SliceDetailsFloatingScreen*>();
        if (!screen->DisplayInPause()) return;
        container->BindInterfacesAndSelfTo<PauseController*>()->AsSingle();
    });

    zenjector->Install(Location::Menu, [](DiContainer* container)
    {
        container->BindInterfacesAndSelfTo<MenuController*>()->AsSingle();
    });
}

BSML_DATACACHE(bloq_grad_png)
{
    return IncludedAssets::bloq_gradient_png;
}

BSML_DATACACHE(bloq_png)
{
    return IncludedAssets::bloq_png;
}

BSML_DATACACHE(bloq_arrow_png)
{
    return IncludedAssets::arrow_png;
}

BSML_DATACACHE(cut_arrow_png)
{
    return IncludedAssets::cut_arrow_png;
}

BSML_DATACACHE(border_png)
{
    return IncludedAssets::border_png;
}

BSML_DATACACHE(dot_png)
{
    return IncludedAssets::dot_png;
}