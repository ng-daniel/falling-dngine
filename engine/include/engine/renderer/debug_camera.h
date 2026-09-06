#pragma once

#include <chrono>

#include <glm/vec3.hpp>

#include "engine/renderer/renderer_structures.h"

class WindowManager;

class DebugCamera {
public:
    FrameUniformData Update(const WindowManager& window);

private:
    glm::vec3 position = glm::vec3(0.0f, 2.0f, 4.0f);
    float yawDegrees = -90.0f;
    float pitchDegrees = -14.0f;
    float aspectRatio = 800.0f / 600.0f;
    std::chrono::steady_clock::time_point lastUpdateTime = std::chrono::steady_clock::now();
};
