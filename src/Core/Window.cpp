#include "CityBuilder/Core/Window.hpp"

#include <stdexcept>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace citybuilder {

Window::Window(const int width, const int height, const std::string_view title)
{
    glfwSetErrorCallback(errorCallback);
    if (glfwInit() != GLFW_TRUE) {
        throw std::runtime_error{"Unable to initialise GLFW"};
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    const std::string ownedTitle{title};
    m_window = glfwCreateWindow(width, height, ownedTitle.c_str(), nullptr, nullptr);
    if (m_window == nullptr) {
        glfwTerminate();
        throw std::runtime_error{"Unable to create the application window"};
    }

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    glfwGetFramebufferSize(m_window, &m_framebufferWidth, &m_framebufferHeight);

    spdlog::info("Created {}x{} window", width, height);
}

Window::~Window()
{
    if (m_window != nullptr) {
        glfwDestroyWindow(m_window);
    }
    glfwTerminate();
}

GLFWwindow* Window::nativeHandle() const noexcept
{
    return m_window;
}

bool Window::shouldClose() const noexcept
{
    return glfwWindowShouldClose(m_window) == GLFW_TRUE;
}

bool Window::isKeyPressed(const int key) const noexcept
{
    return glfwGetKey(m_window, key) == GLFW_PRESS;
}

std::pair<int, int> Window::framebufferSize() const noexcept
{
    return {m_framebufferWidth, m_framebufferHeight};
}

void Window::requestClose() noexcept
{
    glfwSetWindowShouldClose(m_window, GLFW_TRUE);
}

void Window::pollEvents() const noexcept
{
    glfwPollEvents();
}

void Window::swapBuffers() const noexcept
{
    glfwSwapBuffers(m_window);
}

void Window::errorCallback(const int error, const char* description)
{
    spdlog::error("GLFW error {}: {}", error, description);
}

void Window::framebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (self != nullptr) {
        self->m_framebufferWidth = width;
        self->m_framebufferHeight = height;
    }
}

} // namespace citybuilder
