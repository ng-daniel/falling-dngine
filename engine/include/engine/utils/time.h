#pragma once

#include <chrono>

class Time {
public:
    // static class stuff
    Time() = delete;

    /**
     * @brief Resets the clock as if it was just initialized
     */
    static void Reset();

    /**
     * @brief Updates delta time by the time from the last frame
     */
    static void Update();
    static float GetDeltaTime();

private:
    using Clock = std::chrono::steady_clock;

    static Clock::time_point lastFrameTime;
    static float deltaTime;
};
