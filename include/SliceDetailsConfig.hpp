#pragma once

#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/config/config-utils.hpp"
#include <string>
#include <iostream>


std::optional<bool> getBool(rapidjson::Value& obj, std::string_view fieldName, bool required = false);
std::optional<bool> setBool(rapidjson::Value& obj, std::string_view fieldName,  bool value, bool required = false);
std::optional<float> getFloat(rapidjson::Value& obj, std::string_view fieldName, bool required = false);
std::optional<float> setFloat(rapidjson::Value& obj, std::string_view fieldName, float value, bool required = false);

namespace SliceDetails{
    class Config {
    public:
        bool isEnabled;
        bool inPause;
        bool inResults;
        float pausePosX;
        float pausePosY;
        float pausePosZ;
        float pauseRotX;
        float pauseRotY;
        float pauseRotZ;
        float resultPosX;
        float resultPosY;
        float resultPosZ;
        float resultRotX;
        float resultRotY;
        float resultRotZ;
    };
}
class ConfigHelper {
public:
    static bool LoadConfig(SliceDetails::Config& con, ConfigDocument& config);
    static void CreateDefaultConfig(ConfigDocument& config);
};