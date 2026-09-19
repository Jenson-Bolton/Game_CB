#pragma once

#include <chrono>

namespace citybuilder {

/** @brief Tracks rendered-frame time and a fixed-rate simulation accumulator. */
class GameClock final {
public:
    /** Captures elapsed real time and adds it to the simulation accumulator. */
    void tick() noexcept;

    /** @return Clamped duration of the latest rendered frame in seconds. */
    [[nodiscard]] float frameDeltaSeconds() const noexcept;
    /** @return Fixed simulation-step duration in seconds. */
    [[nodiscard]] float fixedDeltaSeconds() const noexcept;
    /** @return Total clamped real time observed by the clock in seconds. */
    [[nodiscard]] float elapsedSeconds() const noexcept;

    /**
     * @brief Consumes one pending fixed simulation step when available.
     * @return True when the caller should run one fixed update.
     */
    [[nodiscard]] bool consumeFixedStep() noexcept;

private:
    using Clock = std::chrono::steady_clock;

    Clock::time_point m_previous{};
    double m_accumulator{};
    float m_frameDeltaSeconds{};
    float m_elapsedSeconds{};
    bool m_started{false};

    static constexpr float kFixedDeltaSeconds = 1.0F / 60.0F;
    static constexpr float kMaximumFrameDeltaSeconds = 0.1F;
};

} // namespace citybuilder
