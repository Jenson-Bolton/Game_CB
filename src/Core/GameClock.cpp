#include "CityBuilder/Core/GameClock.hpp"

#include <algorithm>

namespace citybuilder {

void GameClock::tick() noexcept
{
    const Clock::time_point now = Clock::now();
    if (!m_started) {
        m_previous = now;
        m_started = true;
        return;
    }

    const float realDelta = std::chrono::duration<float>(now - m_previous).count();
    m_previous = now;
    m_frameDeltaSeconds = std::clamp(realDelta, 0.0F, kMaximumFrameDeltaSeconds);
    m_elapsedSeconds += m_frameDeltaSeconds;
    m_accumulator += static_cast<double>(m_frameDeltaSeconds);
}

float GameClock::frameDeltaSeconds() const noexcept
{
    return m_frameDeltaSeconds;
}

float GameClock::fixedDeltaSeconds() const noexcept
{
    return kFixedDeltaSeconds;
}

float GameClock::elapsedSeconds() const noexcept
{
    return m_elapsedSeconds;
}

bool GameClock::consumeFixedStep() noexcept
{
    if (m_accumulator < static_cast<double>(kFixedDeltaSeconds)) {
        return false;
    }

    m_accumulator -= static_cast<double>(kFixedDeltaSeconds);
    return true;
}

} // namespace citybuilder
