#include "CityBuilder/Scene/Camera.hpp"

#include <algorithm>
#include <cmath>

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

#include "CityBuilder/Core/Window.hpp"

namespace citybuilder {
namespace {

constexpr glm::vec3 kWorldUp{0.0F, 1.0F, 0.0F};
constexpr float kMoveSpeed = 5.0F;
constexpr float kLookSpeed = 70.0F;

} // namespace

Camera::Camera(const glm::vec3 position)
    : m_position{position}
{
}

void Camera::update(const Window& window, const float deltaSeconds)
{
    const float moveStep = kMoveSpeed * deltaSeconds;
    const float lookStep = kLookSpeed * deltaSeconds;
    const glm::vec3 facing = forward();
    const glm::vec3 right = glm::normalize(glm::cross(facing, kWorldUp));

    if (window.isKeyPressed(GLFW_KEY_W)) {
        m_position += facing * moveStep;
    }
    if (window.isKeyPressed(GLFW_KEY_S)) {
        m_position -= facing * moveStep;
    }
    if (window.isKeyPressed(GLFW_KEY_A)) {
        m_position -= right * moveStep;
    }
    if (window.isKeyPressed(GLFW_KEY_D)) {
        m_position += right * moveStep;
    }
    if (window.isKeyPressed(GLFW_KEY_Q)) {
        m_position -= kWorldUp * moveStep;
    }
    if (window.isKeyPressed(GLFW_KEY_E)) {
        m_position += kWorldUp * moveStep;
    }

    if (window.isKeyPressed(GLFW_KEY_LEFT)) {
        m_yawDegrees -= lookStep;
    }
    if (window.isKeyPressed(GLFW_KEY_RIGHT)) {
        m_yawDegrees += lookStep;
    }
    if (window.isKeyPressed(GLFW_KEY_UP)) {
        m_pitchDegrees += lookStep;
    }
    if (window.isKeyPressed(GLFW_KEY_DOWN)) {
        m_pitchDegrees -= lookStep;
    }
    m_pitchDegrees = std::clamp(m_pitchDegrees, -89.0F, 89.0F);
}

glm::mat4 Camera::viewMatrix() const
{
    return glm::lookAt(m_position, m_position + forward(), kWorldUp);
}

glm::mat4 Camera::projectionMatrix(const float aspectRatio) const
{
    return glm::perspective(glm::radians(60.0F), aspectRatio, 0.1F, 500.0F);
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

} // namespace citybuilder
