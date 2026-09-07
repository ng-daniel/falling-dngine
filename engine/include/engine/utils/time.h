#pragma once

#include <chrono>
#include <cstdint>

class Time {
public:
    // static class stuff
    Time() = delete;

    static void SetFpsTrackingInterval(float interval) { FPS_SAMPLE_INTERVAL = interval; }
    static void ToggleFPSTracking(bool track) { trackFps = track; }
    static void ToggleFPSLogging(bool log) { logFps = log; }

    /**
     * @brief Resets the clock as if it was just initialized
     */
    static void Reset();

    /**
     * @brief Updates delta time by the time from the last frame
     */
    static void Update();
    static float GetDeltaTime();
    static float GetFPS();

private:
    using Clock = std::chrono::steady_clock;

    static bool initialized; 

    static Clock::time_point lastFrameTime;
    static float deltaTime;

    static float FPS_SAMPLE_INTERVAL; // interval in seconds to sample FPS
    static bool trackFps; // should time track the FPS
    static bool logFps; // should time log the FPS to console
    static float fpsSampleElapsedTime;
    static float framesPerSecond;
    static std::uint32_t fpsFrameCount;

    static void TrackFPS();
};
