#pragma once

#include "engine/core/window_manager.h"
#include "engine/input/input_structures.h"

class InputManager {
public:
    InputManager(WindowManager& windowManager);
    ~InputManager();

    void Update();
    bool IsKeyPressed(KeyCode key);
    bool IsKeyDown(KeyCode key);
    bool IsMouseButtonPressed(KeyCode button);
private:
    WindowManager& windowManager;
};