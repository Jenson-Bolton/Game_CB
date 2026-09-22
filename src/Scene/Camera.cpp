#include "CityBuilder/Scene/Camera.hpp"

#include <algorithm>
#include <cmath>

#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

namespace citybuilder {
namespace {

constexpr glm::vec3 worldUp{0.0F, 1.0F, 0.0F};
constexpr float minimumPitchDegrees = 8.0F;
constexpr float maximumPitchDegrees = 85.0F;
constexpr float minimumDistance = 2.0F;
constexpr float maximumDistance = 160.0F;

} // namespace

Camera::Camera() = default;

glm::mat4 Camera::viewMatrix() const
{
    return glm::lookAt(position(), m_target, worldUp);
}

glm::mat4 Camera::projectionMatrix(const float aspectRatio) const
{
    const float safeAspectRatio = aspectRatio > 0.0F ? aspectRatio : 1.0F;
    return glm::perspective(
        glm::radians(m_fieldOfViewDegrees),
        safeAspectRatio,
        0.1F,
        2500.0F
    );
}

glm::vec3 Camera::position() const
{
    const float yaw = glm::radians(m_yawDegrees);
    const float pitch = glm::radians(m_pitchDegrees);
    const float horizontalDistance = m_distance * std::cos(pitch);

    return m_target + glm::vec3{
        horizontalDistance * std::sin(yaw),
        m_distance * std::sin(pitch),
        horizontalDistance * std::cos(yaw)
    };
}

float Camera::distance() const noexcept
{
    return m_distance;
}

void Camera::orbit(
    const float yawDeltaDegrees,
    const float pitchDeltaDegrees
) noexcept
{
    m_yawDegrees = std::fmod(m_yawDegrees + yawDeltaDegrees, 360.0F);
    m_pitchDegrees = std::clamp(
        m_pitchDegrees + pitchDeltaDegrees,
        minimumPitchDegrees,
        maximumPitchDegrees
    );
}

void Camera::pan(const float rightDistance, const float forwardDistance) noexcept
{
    m_target += planarRight() * rightDistance;
    m_target += planarForward() * forwardDistance;
}

void Camera::zoom(const float scrollSteps) noexcept
{
    m_distance *= std::pow(0.85F, scrollSteps);
    m_distance = std::clamp(m_distance, minimumDistance, maximumDistance);
}

glm::vec3 Camera::planarForward() const
{
    glm::vec3 forward = m_target - position();
    forward.y = 0.0F;
    return glm::normalize(forward);
}

glm::vec3 Camera::planarRight() const
{
    return glm::normalize(glm::cross(planarForward(), worldUp));
}

} // namespace citybuilder
