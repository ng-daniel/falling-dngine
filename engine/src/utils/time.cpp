#include "engine/utils/time.h"

Time::Clock::time_point Time::lastFrameTime = Time::Clock::now();
float Time::deltaTime = 0.0f;

void Time::Reset() {
    lastFrameTime = Clock::now();
    deltaTime = 0.0f;
}

void Time::Update() {
    const Clock::time_point currentFrameTime = Clock::now();
    deltaTime = std::chrono::duration<float>(currentFrameTime - lastFrameTime).count();
    lastFrameTime = currentFrameTime;
}

float Time::GetDeltaTime() {
    return deltaTime;
}
