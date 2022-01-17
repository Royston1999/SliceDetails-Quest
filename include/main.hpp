#pragma once

// Include the modloader header, which allows us to tell the modloader which mod this is, and the version etc.
#include "modloader/shared/modloader.hpp"
#include "SliceDetailsConfig.hpp"
#include "HMUI/ModalView.hpp"
#include "Data/GridInfo.hpp"
#include "UnityEngine/Material.hpp"
// beatsaber-hook is a modding framework that lets us call functions and fetch field values from in the game
// It also allows creating objects, configuration, and importantly, hooking methods to modify their values
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"

namespace SliceDetails{
    class Main{
        public:
            static Config config;
            static bool configValid;
            static void loadConfig();
            static HMUI::ModalView* modal;
            static GridInfo* gridNotes[12];
            static void updateModalNotes(int index);
            static bool isPaused;
            static UnityEngine::Material* UINoGlow;
    };
}

// Define these functions here so that we can easily read configuration and log information from other files
Configuration& getConfig();
Logger& getLogger();