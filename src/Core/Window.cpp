#include "CityBuilder/Core/Window.hpp"

#include <algorithm>
#include <array>
#include <optional>
#include <stdexcept>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace citybuilder {
namespace {

struct KeyRange {
    int glfwFirst;
    int glfwLast;
    Key firstKey;
};

struct KeyMapping {
    int glfwKey;
    Key key;
};

struct MouseButtonMapping {
    int glfwButton;
    MouseButton button;
};

constexpr auto kKeyRanges = std::to_array<KeyRange>({
    {GLFW_KEY_A, GLFW_KEY_Z, Key::A},
    {GLFW_KEY_0, GLFW_KEY_9, Key::Num0},
    {GLFW_KEY_F1, GLFW_KEY_F12, Key::F1},
});

static_assert(static_cast<int>(Key::Z) - static_cast<int>(Key::A) == GLFW_KEY_Z - GLFW_KEY_A);
static_assert(
    static_cast<int>(Key::Num9) - static_cast<int>(Key::Num0) == GLFW_KEY_9 - GLFW_KEY_0
);
static_assert(
    static_cast<int>(Key::F12) - static_cast<int>(Key::F1) == GLFW_KEY_F12 - GLFW_KEY_F1
);

constexpr auto kKeyMappings = std::to_array<KeyMapping>({
    {GLFW_KEY_SPACE, Key::Space},
    {GLFW_KEY_APOSTROPHE, Key::Apostrophe},
    {GLFW_KEY_COMMA, Key::Comma},
    {GLFW_KEY_MINUS, Key::Minus},
    {GLFW_KEY_PERIOD, Key::Period},
    {GLFW_KEY_SLASH, Key::Slash},
    {GLFW_KEY_SEMICOLON, Key::Semicolon},
    {GLFW_KEY_EQUAL, Key::Equal},
    {GLFW_KEY_LEFT_BRACKET, Key::LeftBracket},
    {GLFW_KEY_BACKSLASH, Key::Backslash},
    {GLFW_KEY_RIGHT_BRACKET, Key::RightBracket},
    {GLFW_KEY_GRAVE_ACCENT, Key::GraveAccent},
    {GLFW_KEY_ESCAPE, Key::Escape},
    {GLFW_KEY_ENTER, Key::Enter},
    {GLFW_KEY_TAB, Key::Tab},
    {GLFW_KEY_BACKSPACE, Key::Backspace},
    {GLFW_KEY_CAPS_LOCK, Key::CapsLock},
    {GLFW_KEY_LEFT_SHIFT, Key::LeftShift},
    {GLFW_KEY_RIGHT_SHIFT, Key::RightShift},
    {GLFW_KEY_LEFT_CONTROL, Key::LeftControl},
    {GLFW_KEY_RIGHT_CONTROL, Key::RightControl},
    {GLFW_KEY_LEFT_ALT, Key::LeftAlt},
    {GLFW_KEY_RIGHT_ALT, Key::RightAlt},
    {GLFW_KEY_LEFT_SUPER, Key::LeftSuper},
    {GLFW_KEY_MENU, Key::Menu},
    {GLFW_KEY_UP, Key::ArrowUp},
    {GLFW_KEY_DOWN, Key::ArrowDown},
    {GLFW_KEY_LEFT, Key::ArrowLeft},
    {GLFW_KEY_RIGHT, Key::ArrowRight},
});

constexpr auto kMouseButtonMappings = std::to_array<MouseButtonMapping>({
    {GLFW_MOUSE_BUTTON_LEFT, MouseButton::Left},
    {GLFW_MOUSE_BUTTON_MIDDLE, MouseButton::Middle},
    {GLFW_MOUSE_BUTTON_RIGHT, MouseButton::Right},
});

[[nodiscard]] std::optional<Key> translateKey(const int glfwKey)
{
    for (const KeyRange& range : kKeyRanges) {
        if (glfwKey >= range.glfwFirst && glfwKey <= range.glfwLast) {
            const int first = static_cast<int>(range.firstKey);
            return static_cast<Key>(first + glfwKey - range.glfwFirst);
        }
    }

    const auto mapping = std::find_if(
        kKeyMappings.begin(),
        kKeyMappings.end(),
        [glfwKey](const KeyMapping& candidate) { return candidate.glfwKey == glfwKey; }
    );
    return mapping == kKeyMappings.end() ? std::nullopt : std::optional<Key>{mapping->key};
}

[[nodiscard]] std::optional<MouseButton> translateMouseButton(const int glfwButton)
{
    const auto mapping = std::find_if(
        kMouseButtonMappings.begin(),
        kMouseButtonMappings.end(),
        [glfwButton](const MouseButtonMapping& candidate) {
            return candidate.glfwButton == glfwButton;
        }
    );
    return mapping == kMouseButtonMappings.end()
        ? std::nullopt
        : std::optional<MouseButton>{mapping->button};
}

} // namespace

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
    glfwSetKeyCallback(m_window, keyCallback);
    glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
    glfwSetCursorPosCallback(m_window, cursorPositionCallback);
    glfwSetScrollCallback(m_window, scrollCallback);
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

std::pair<int, int> Window::framebufferSize() const noexcept
{
    return {m_framebufferWidth, m_framebufferHeight};
}

Input& Window::input() noexcept
{
    return m_input;
}

const Input& Window::input() const noexcept
{
    return m_input;
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

void Window::keyCallback(
    GLFWwindow* window,
    const int key,
    int,
    const int action,
    int
)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    const std::optional<Key> translated = translateKey(key);
    if (self != nullptr && translated.has_value()) {
        self->m_input.setKey(*translated, action != GLFW_RELEASE);
    }
}

void Window::mouseButtonCallback(
    GLFWwindow* window,
    const int button,
    const int action,
    int
)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    const std::optional<MouseButton> translated = translateMouseButton(button);
    if (self != nullptr && translated.has_value()) {
        self->m_input.setMouseButton(*translated, action != GLFW_RELEASE);
    }
}

void Window::cursorPositionCallback(GLFWwindow* window, const double x, const double y)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (self != nullptr) {
        self->m_input.setCursorPosition(x, y);
    }
}

void Window::scrollCallback(GLFWwindow* window, double, const double yOffset)
{
    auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (self != nullptr) {
        self->m_input.addScroll(yOffset);
    }
}

} // namespace citybuilder
