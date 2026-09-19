#include "CityBuilder/Scene/Camera.hpp"

#include <algorithm>
#include <cmath>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

namespace citybuilder {
namespace {

constexpr glm::vec3 kWorldUp{0.0F, 1.0F, 0.0F};

} // namespace

Camera::Camera(const glm::vec3 position)
    : m_position{position}
{
}

void Camera::setPosition(const glm::vec3 position) noexcept
{
    m_position = position;
}

void Camera::setOrientation(const float yawDegrees, const float pitchDegrees) noexcept
{
    m_yawDegrees = yawDegrees;
    m_pitchDegrees = std::clamp(pitchDegrees, -89.0F, 89.0F);
}

void Camera::setFieldOfView(const float fieldOfViewDegrees) noexcept
{
    m_fieldOfViewDegrees = std::clamp(fieldOfViewDegrees, 20.0F, 100.0F);
}

const glm::vec3& Camera::position() const noexcept
{
    return m_position;
}

glm::vec3 Camera::forward() const
{
    const float yaw = glm::radians(m_yawDegrees);
    const float pitch = glm::radians(m_pitchDegrees);
    return glm::normalize(glm::vec3{
        std::cos(yaw) * std::cos(pitch),
        std::sin(pitch),
        std::sin(yaw) * std::cos(pitch),
    });
}

glm::vec3 Camera::right() const
{
    return glm::normalize(glm::cross(forward(), kWorldUp));
}

glm::mat4 Camera::viewMatrix() const
{
    return glm::lookAt(m_position, m_position + forward(), kWorldUp);
}

glm::mat4 Camera::projectionMatrix(const float aspectRatio) const
{
    return glm::perspective(glm::radians(m_fieldOfViewDegrees), aspectRatio, 0.1F, 500.0F);
}

} // namespace citybuilder
