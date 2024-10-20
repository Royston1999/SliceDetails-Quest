#pragma once

#define SLICE_DETAILS_EXPORT __attribute__((visibility("default")))
#ifdef __cplusplus
#define SLICE_DETAILS_EXPORT_FUNC extern "C" SLICE_DETAILS_EXPORT
#else
#define BSS_EXPORT_FUNC SLICE_DETAILS_EXPORT
#endif

// Include the modloader header, which allows us to tell the modloader which mod this is, and the version etc.
#include "scotland2/shared/loader.hpp"
// beatsaber-hook is a modding framework that lets us call functions and fetch field values from in the game
// It also allows creating objects, configuration, and importantly, hooking methods to modify their values
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"

// Define these functions here so that we can easily read configuration and log information from other files
Configuration& getConfig();
const Paper::ConstLoggerContext<13UL>& getLogger();