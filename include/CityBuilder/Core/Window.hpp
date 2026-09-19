#pragma once

#include <string_view>
#include <utility>

#include "CityBuilder/Core/Input.hpp"

struct GLFWwindow;

namespace citybuilder {

/** RAII wrapper around a GLFW window and the GLFW library lifetime. */
class Window final {
public:
    /** Creates a window with an OpenGL 3.3 core context. */
    Window(int width, int height, std::string_view title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    /** Returns the native handle used by rendering integrations. */
    [[nodiscard]] GLFWwindow* nativeHandle() const noexcept;
    /** Reports whether the window has been asked to close. */
    [[nodiscard]] bool shouldClose() const noexcept;
    /** Returns the drawable framebuffer dimensions in pixels. */
    [[nodiscard]] std::pair<int, int> framebufferSize() const noexcept;
    /** @return Mutable input state populated by the window callbacks. */
    [[nodiscard]] Input& input() noexcept;
    /** @return Read-only input state populated by the window callbacks. */
    [[nodiscard]] const Input& input() const noexcept;

    /** Marks the window to close at the end of the current frame. */
    void requestClose() noexcept;
    /** Processes queued window and input events. */
    void pollEvents() const noexcept;
    /** Presents the completed back buffer. */
    void swapBuffers() const noexcept;

private:
    static void errorCallback(int error, const char* description);
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    static void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int modifiers);
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int modifiers);
    static void cursorPositionCallback(GLFWwindow* window, double x, double y);
    static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

    GLFWwindow* m_window{nullptr};
    Input m_input;
    int m_framebufferWidth{0};
    int m_framebufferHeight{0};
};

} // namespace citybuilder
