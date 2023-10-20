#pragma once

#include "config-utils/shared/config-utils.hpp"
#include "UnityEngine/Vector3.hpp"

DECLARE_CONFIG(SliceDetailsConfig,
    CONFIG_VALUE(inPause, bool, "inPause", true);
    CONFIG_VALUE(inResults, bool, "inResults", true);
    CONFIG_VALUE(pausePos, UnityEngine::Vector3, "pausePos", UnityEngine::Vector3(-1.648f, 1.516f, 0.916f));
    CONFIG_VALUE(pauseRot, UnityEngine::Vector3, "pauseRot", UnityEngine::Vector3(1.120f, 286.746f, 2.421f));
    CONFIG_VALUE(resultsPos, UnityEngine::Vector3, "resultsPos", UnityEngine::Vector3(2.321f, 2.883f, 3.851f));
    CONFIG_VALUE(resultsRot, UnityEngine::Vector3, "resultsRot", UnityEngine::Vector3(338.810f, 30.401f, 359.280f));
)