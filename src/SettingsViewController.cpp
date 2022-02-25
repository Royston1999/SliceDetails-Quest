#include "SettingsViewController.hpp"

DEFINE_TYPE(SliceDetails, SettingsViewController);

void SliceDetails::SettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
{
    if (firstActivation){
        auto* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(get_transform());
        QuestUI::BeatSaberUI::CreateToggle(container->get_transform(), "Enable in Pause Menu", Main::config.inPause, [](bool value){
            setBool(getConfig().config, "inPause", value, false);
        });
        QuestUI::BeatSaberUI::CreateToggle(container->get_transform(), "Enable on Results Screen", Main::config.inResults, [](bool value){
            setBool(getConfig().config, "inResults", value, false);
        });
    }
}