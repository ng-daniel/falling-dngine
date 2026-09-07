#include "engine/utils/time.h"
#include "engine/debug/logger.h"

#include <string>

Time::Clock::time_point Time::lastFrameTime = Time::Clock::now();
float Time::deltaTime = 0.0f;
float Time::FPS_SAMPLE_INTERVAL = 1.0f;
bool Time::trackFps = true;
bool Time::logFps = false;
float Time::fpsSampleElapsedTime = 0.0f;
float Time::framesPerSecond = 0.0f;
std::uint32_t Time::fpsFrameCount = 0;

void Time::Reset() {
    lastFrameTime = Clock::now();
    deltaTime = 0.0f;
    fpsSampleElapsedTime = 0.0f;
    framesPerSecond = 0.0f;
    fpsFrameCount = 0;
}

void Time::Update() {    
    const Clock::time_point currentFrameTime = Clock::now();
    deltaTime = std::chrono::duration<float>(currentFrameTime - lastFrameTime).count();
    lastFrameTime = currentFrameTime;

    if (trackFps) {
        TrackFPS();
    }
}

void Time::TrackFPS() {
    fpsSampleElapsedTime += deltaTime;
    fpsFrameCount++;

    if (fpsSampleElapsedTime >= FPS_SAMPLE_INTERVAL) {
        // compute FPS as frames per second over the last interval
        framesPerSecond = static_cast<float>(fpsFrameCount) / fpsSampleElapsedTime;
        
        if (logFps) {
            // round to nearest integer
            const std::uint32_t displayedFPS = static_cast<std::uint32_t>(framesPerSecond + 0.5f);
            Logger::Info("Time", "FPS: " + std::to_string(displayedFPS));
        }

        // reset counters
        fpsSampleElapsedTime = 0.0f;
        fpsFrameCount = 0;
    }
}

float Time::GetDeltaTime() {
    return deltaTime;
}

float Time::GetFPS() {
    return framesPerSecond;
}
