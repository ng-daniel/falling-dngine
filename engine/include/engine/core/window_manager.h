#pragma once

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>
#include <functional>

class WindowManager {
public:
    ~WindowManager();

    bool Init(const std::function<void()>& configure = {});
    bool ShouldClose() const;
    void ForceClose();
    void BeginFrame();
    void EndFrame();
    void Close();

    bool IsKeyDown(int key) const;
    void GetFramebufferSize(int& width, int& height) const;
private:
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    GLFWwindow * handle = nullptr;
    bool forceClose = false;
    std::array<bool, GLFW_KEY_LAST + 1> keyStates{};
};
