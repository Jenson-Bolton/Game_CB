#include "CityBuilder/Core/Input.hpp"

namespace citybuilder {

void Input::beginFrame() noexcept
{
    m_previousKeys = m_currentKeys;
    m_previousMouseButtons = m_currentMouseButtons;
    m_mouseDelta = glm::vec2{0.0F};
    m_scrollDelta = 0.0F;
}

void Input::setKey(const Key key, const bool pressed) noexcept
{
    m_currentKeys[index(key)] = pressed;
}

void Input::setMouseButton(const MouseButton button, const bool pressed) noexcept
{
    m_currentMouseButtons[index(button)] = pressed;
}

void Input::setCursorPosition(const double x, const double y) noexcept
{
    const glm::vec2 newPosition{static_cast<float>(x), static_cast<float>(y)};

    if (!m_hasMousePosition) {
        m_mousePosition = newPosition;
        m_hasMousePosition = true;
        return;
    }

    m_mouseDelta += newPosition - m_mousePosition;
    m_mousePosition = newPosition;
}

void Input::addScroll(const double offset) noexcept
{
    m_scrollDelta += static_cast<float>(offset);
}

bool Input::isKeyDown(const Key key) const noexcept
{
    return m_currentKeys[index(key)];
}

bool Input::wasKeyPressed(const Key key) const noexcept
{
    const std::size_t keyIndex = index(key);
    return m_currentKeys[keyIndex] && !m_previousKeys[keyIndex];
}

bool Input::wasKeyReleased(const Key key) const noexcept
{
    const std::size_t keyIndex = index(key);
    return !m_currentKeys[keyIndex] && m_previousKeys[keyIndex];
}

bool Input::isMouseButtonDown(const MouseButton button) const noexcept
{
    return m_currentMouseButtons[index(button)];
}

bool Input::wasMouseButtonPressed(const MouseButton button) const noexcept
{
    const std::size_t buttonIndex = index(button);
    return m_currentMouseButtons[buttonIndex] && !m_previousMouseButtons[buttonIndex];
}

bool Input::wasMouseButtonReleased(const MouseButton button) const noexcept
{
    const std::size_t buttonIndex = index(button);
    return !m_currentMouseButtons[buttonIndex] && m_previousMouseButtons[buttonIndex];
}

glm::vec2 Input::mousePosition() const noexcept
{
    return m_mousePosition;
}

glm::vec2 Input::mouseDelta() const noexcept
{
    return m_mouseDelta;
}

float Input::scrollDelta() const noexcept
{
    return m_scrollDelta;
}

} // namespace citybuilder
