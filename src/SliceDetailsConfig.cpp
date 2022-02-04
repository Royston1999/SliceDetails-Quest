#include <tuple>
#include "SliceDetailsConfig.hpp"
#include "main.hpp"

#define GET(obj, fieldName, method, required) auto itr = obj.FindMember(fieldName.data()); \
if (itr == obj.MemberEnd()) { \
    if (required) { \
    } \
    return std::nullopt; \
} \
return itr->value.method()

using namespace rapidjson;

std::optional<bool> getBool(Value& obj, std::string_view fieldName, bool required) {
    GET(obj, fieldName, GetBool, required);
}

std::optional<int> getInt(Value& obj, std::string_view fieldName, bool required) {
    GET(obj, fieldName, GetInt, required);
}

std::optional<float> getFloat(Value& obj, std::string_view fieldName, bool required) {
    GET(obj, fieldName, GetFloat, required);
}

std::optional<bool> setBool(Value& obj, std::string_view fieldName, bool value, bool required) {
    auto itr = obj.FindMember(fieldName.data());
    if (itr == obj.MemberEnd()) {
        if (required) {
        }
    }
    itr->value.SetBool(value);
    return true;
}

std::optional<int> setInt(Value& obj, std::string_view fieldName, int value, bool required) {
    auto itr = obj.FindMember(fieldName.data());
    if (itr == obj.MemberEnd()) {
        if (required) {
        }
    }
    itr->value.SetInt(value);
    return true;
}

std::optional<float> setFloat(Value& obj, std::string_view fieldName, float value, bool required) {
    auto itr = obj.FindMember(fieldName.data());
    if (itr == obj.MemberEnd()) {
        if (required) {
        }
    }
    itr->value.SetFloat(value);
    return true;
}

bool ConfigHelper::LoadConfig(SliceDetails::Config& con, ConfigDocument& config) {
    if (!config.HasMember("inPause")) ConfigHelper::CreateDefaultConfig(config);
    con.inPause = getBool(config, "inPause").value_or(false);
    con.inResults = getBool(config, "inResults").value_or(false);
    con.pausePosX = getFloat(config, "pausePosX").value_or(0);
    con.pausePosY = getFloat(config, "pausePosY").value_or(1);
    con.pausePosZ = getFloat(config, "pausePosZ").value_or(1);
    con.pauseRotX = getFloat(config, "pauseRotX").value_or(0);
    con.pauseRotY = getFloat(config, "pauseRotY").value_or(0);
    con.pauseRotZ = getFloat(config, "pauseRotZ").value_or(0);

    con.resultPosX = getFloat(config, "resultPosX").value_or(0);
    con.resultPosY = getFloat(config, "resultPosY").value_or(1);
    con.resultPosZ = getFloat(config, "resultPosZ").value_or(1);
    con.resultRotX = getFloat(config, "resultRotX").value_or(0);
    con.resultRotY = getFloat(config, "resultRotY").value_or(0);
    con.resultRotZ = getFloat(config, "resultRotZ").value_or(0);
    return true;
}

void ConfigHelper::CreateDefaultConfig(ConfigDocument& config){
    config.SetObject();
    config.RemoveAllMembers();
    config.AddMember("inPause", true, config.GetAllocator());
    config.AddMember("inResults", true, config.GetAllocator());
    getConfig().Write();
    config.AddMember("pausePosX", -1.648f, config.GetAllocator());
    config.AddMember("pausePosY", 1.516, config.GetAllocator());
    config.AddMember("pausePosZ", 0.916f, config.GetAllocator());
    config.AddMember("pauseRotX", 1.120f, config.GetAllocator());
    config.AddMember("pauseRotY", 286.746f, config.GetAllocator());
    config.AddMember("pauseRotZ", 2.421f, config.GetAllocator());
    getConfig().Write();
    config.AddMember("resultPosX", 2.321f, config.GetAllocator());
    config.AddMember("resultPosY", 2.883f, config.GetAllocator());
    config.AddMember("resultPosZ", 3.851f, config.GetAllocator());
    config.AddMember("resultRotX", 338.810f, config.GetAllocator());
    config.AddMember("resultRotY", 30.401f, config.GetAllocator());
    config.AddMember("resultRotZ", 359.280f, config.GetAllocator());
    getConfig().Write();
}