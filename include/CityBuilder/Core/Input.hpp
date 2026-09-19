#pragma once

#include <bitset>
#include <cstddef>
#include <cstdint>

#include <glm/vec2.hpp>

namespace citybuilder {

/**
 * @brief Keyboard keys supported by the application's 60% keyboard profile.
 *
 * Letter, number, punctuation, modifier, and editing keys correspond to the
 * physical keys found on a conventional ANSI 60% keyboard. Arrow and F1-F12
 * values represent logical keys normally produced through the keyboard's
 * firmware-controlled Fn layer.
 */
enum class Key : std::uint8_t {
    A, ///< A key.
    B, ///< B key.
    C, ///< C key.
    D, ///< D key.
    E, ///< E key.
    F, ///< F key.
    G, ///< G key.
    H, ///< H key.
    I, ///< I key.
    J, ///< J key.
    K, ///< K key.
    L, ///< L key.
    M, ///< M key.
    N, ///< N key.
    O, ///< O key.
    P, ///< P key.
    Q, ///< Q key.
    R, ///< R key.
    S, ///< S key.
    T, ///< T key.
    U, ///< U key.
    V, ///< V key.
    W, ///< W key.
    X, ///< X key.
    Y, ///< Y key.
    Z, ///< Z key.

    Num0, ///< Number-row 0 key.
    Num1, ///< Number-row 1 key.
    Num2, ///< Number-row 2 key.
    Num3, ///< Number-row 3 key.
    Num4, ///< Number-row 4 key.
    Num5, ///< Number-row 5 key.
    Num6, ///< Number-row 6 key.
    Num7, ///< Number-row 7 key.
    Num8, ///< Number-row 8 key.
    Num9, ///< Number-row 9 key.

    F1, ///< Logical F1 key, normally reached through Fn+1.
    F2, ///< Logical F2 key, normally reached through Fn+2.
    F3, ///< Logical F3 key, normally reached through Fn+3.
    F4, ///< Logical F4 key, normally reached through Fn+4.
    F5, ///< Logical F5 key, normally reached through Fn+5.
    F6, ///< Logical F6 key, normally reached through Fn+6.
    F7, ///< Logical F7 key, normally reached through Fn+7.
    F8, ///< Logical F8 key, normally reached through Fn+8.
    F9, ///< Logical F9 key, normally reached through Fn+9.
    F10, ///< Logical F10 key, normally reached through Fn+0.
    F11, ///< Logical F11 key, normally reached through the Fn layer.
    F12, ///< Logical F12 key, normally reached through the Fn layer.

    Space, ///< Space bar.
    Apostrophe, ///< Apostrophe and quotation-mark key.
    Comma, ///< Comma and less-than key.
    Minus, ///< Minus and underscore key.
    Period, ///< Period and greater-than key.
    Slash, ///< Slash and question-mark key.
    Semicolon, ///< Semicolon and colon key.
    Equal, ///< Equals and plus key.
    LeftBracket, ///< Left bracket and brace key.
    Backslash, ///< Backslash and pipe key.
    RightBracket, ///< Right bracket and brace key.
    GraveAccent, ///< Grave-accent and tilde key.

    Escape, ///< Escape key.
    Enter, ///< Enter key.
    Tab, ///< Tab key.
    Backspace, ///< Backspace key.
    CapsLock, ///< Caps Lock key.

    LeftShift, ///< Left Shift key.
    RightShift, ///< Right Shift key.
    LeftControl, ///< Left Control key.
    RightControl, ///< Right Control key.
    LeftAlt, ///< Left Alt key.
    RightAlt, ///< Right Alt key.
    LeftSuper, ///< Left Windows, Command, or Super key.
    Menu, ///< Application menu key when present on the keyboard.

    ArrowUp, ///< Logical up-arrow key produced by the Fn layer.
    ArrowDown, ///< Logical down-arrow key produced by the Fn layer.
    ArrowLeft, ///< Logical left-arrow key produced by the Fn layer.
    ArrowRight, ///< Logical right-arrow key produced by the Fn layer.

    Count ///< Number of supported key values; not an input key.
};

/** @brief Mouse buttons recognised by the application. */
enum class MouseButton : std::uint8_t {
    Left, ///< Primary mouse button.
    Middle, ///< Middle mouse button or wheel click.
    Right, ///< Secondary mouse button.
    Count ///< Number of supported mouse buttons; not an input button.
};

/**
 * @brief Stores keyboard and mouse state for the current rendered frame.
 *
 * Window callbacks populate this object. Call beginFrame() before polling
 * window events so edge-triggered and pointer-delta queries are frame-local.
 */
class Input final {
public:
    /** Copies current button states and resets per-frame pointer values. */
    void beginFrame() noexcept;

    /**
     * @brief Updates a keyboard key.
     * @param key Key to update.
     * @param pressed True while the key is pressed.
     */
    void setKey(Key key, bool pressed) noexcept;

    /**
     * @brief Updates a mouse button.
     * @param button Mouse button to update.
     * @param pressed True while the button is pressed.
     */
    void setMouseButton(MouseButton button, bool pressed) noexcept;

    /**
     * @brief Records a cursor position and accumulates this frame's movement.
     * @param x Horizontal cursor position in window coordinates.
     * @param y Vertical cursor position in window coordinates.
     */
    void setCursorPosition(double x, double y) noexcept;

    /**
     * @brief Adds vertical wheel movement to the current frame.
     * @param offset Vertical scroll offset from the window system.
     */
    void addScroll(double offset) noexcept;

    /** @return True while the requested key is held. */
    [[nodiscard]] bool isKeyDown(Key key) const noexcept;
    /** @return True only during the frame in which the key was pressed. */
    [[nodiscard]] bool wasKeyPressed(Key key) const noexcept;
    /** @return True only during the frame in which the key was released. */
    [[nodiscard]] bool wasKeyReleased(Key key) const noexcept;

    /** @return True while the requested mouse button is held. */
    [[nodiscard]] bool isMouseButtonDown(MouseButton button) const noexcept;
    /** @return True only during the frame in which the mouse button was pressed. */
    [[nodiscard]] bool wasMouseButtonPressed(MouseButton button) const noexcept;
    /** @return True only during the frame in which the mouse button was released. */
    [[nodiscard]] bool wasMouseButtonReleased(MouseButton button) const noexcept;

    /** @return Latest cursor position in window coordinates. */
    [[nodiscard]] glm::vec2 mousePosition() const noexcept;
    /** @return Accumulated cursor movement during the current frame. */
    [[nodiscard]] glm::vec2 mouseDelta() const noexcept;
    /** @return Accumulated vertical wheel movement during the current frame. */
    [[nodiscard]] float scrollDelta() const noexcept;

private:
    static constexpr std::size_t kKeyCount = static_cast<std::size_t>(Key::Count);
    static constexpr std::size_t kMouseButtonCount =
        static_cast<std::size_t>(MouseButton::Count);

    [[nodiscard]] static constexpr std::size_t index(const Key key) noexcept
    {
        return static_cast<std::size_t>(key);
    }

    [[nodiscard]] static constexpr std::size_t index(const MouseButton button) noexcept
    {
        return static_cast<std::size_t>(button);
    }

    std::bitset<kKeyCount> m_currentKeys;
    std::bitset<kKeyCount> m_previousKeys;
    std::bitset<kMouseButtonCount> m_currentMouseButtons;
    std::bitset<kMouseButtonCount> m_previousMouseButtons;

    glm::vec2 m_mousePosition{};
    glm::vec2 m_mouseDelta{};
    float m_scrollDelta{};
    bool m_hasMousePosition{false};
};

} // namespace citybuilder
