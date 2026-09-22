#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace citybuilder {

class Camera final {
public:
    Camera();

    [[nodiscard]] glm::mat4 viewMatrix() const;
    [[nodiscard]] glm::mat4 projectionMatrix(float aspectRatio) const;
    [[nodiscard]] glm::vec3 position() const;
    [[nodiscard]] float distance() const noexcept;

    void orbit(float yawDeltaDegrees, float pitchDeltaDegrees) noexcept;
    void pan(float rightDistance, float forwardDistance) noexcept;
    void zoom(float scrollSteps) noexcept;

private:
    [[nodiscard]] glm::vec3 planarForward() const;
    [[nodiscard]] glm::vec3 planarRight() const;

    glm::vec3 m_target{0.0F, 0.0F, 0.0F};
    float m_yawDegrees = 45.0F;
    float m_pitchDegrees = 45.0F;
    float m_distance = 24.0F;
    float m_fieldOfViewDegrees = 45.0F;
};

} // namespace citybuilder
