#include "CityBuilder/Scene/CameraController.hpp"

#include <algorithm>
#include <cmath>

#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

#include "CityBuilder/Core/Input.hpp"
#include "CityBuilder/Scene/Camera.hpp"

namespace citybuilder {
namespace {

constexpr glm::vec3 kWorldUp{0.0F, 1.0F, 0.0F};
constexpr float kKeyboardPanSpeed = 18.0F;
constexpr float kKeyboardOrbitSpeed = 70.0F;
constexpr float kMouseOrbitSensitivity = 0.18F;
constexpr float kMousePanScale = 0.0018F;
constexpr float kZoomScale = 0.12F;
constexpr float kMinimumDistance = 5.0F;
constexpr float kMaximumDistance = 100.0F;
constexpr float kMinimumPitch = -80.0F;
constexpr float kMaximumPitch = -20.0F;

[[nodiscard]] glm::vec3 planarForward(const float yawDegrees)
{
    const float yaw = glm::radians(yawDegrees);
    return glm::normalize(glm::vec3{std::cos(yaw), 0.0F, std::sin(yaw)});
}

} // namespace

CameraController::CameraController(Camera& camera)
    : m_camera{camera}
{
    applyToCamera();
}

void CameraController::update(const Input& input, const float deltaSeconds)
{
    const glm::vec3 forward = planarForward(m_yawDegrees);
    const glm::vec3 right = glm::normalize(glm::cross(forward, kWorldUp));
    const float keyboardPan = kKeyboardPanSpeed * deltaSeconds;

    if (input.isKeyDown(Key::W)) {
        m_focusPoint += forward * keyboardPan;
    }
    if (input.isKeyDown(Key::S)) {
        m_focusPoint -= forward * keyboardPan;
    }
    if (input.isKeyDown(Key::A)) {
        m_focusPoint -= right * keyboardPan;
    }
    if (input.isKeyDown(Key::D)) {
        m_focusPoint += right * keyboardPan;
    }

    const glm::vec2 mouseDelta = input.mouseDelta();
    if (input.isMouseButtonDown(MouseButton::Middle)) {
        const float mousePan = kMousePanScale * m_distance;
        m_focusPoint -= right * mouseDelta.x * mousePan;
        m_focusPoint += forward * mouseDelta.y * mousePan;
    }
    if (input.isMouseButtonDown(MouseButton::Right)) {
        m_yawDegrees += mouseDelta.x * kMouseOrbitSensitivity;
        m_pitchDegrees -= mouseDelta.y * kMouseOrbitSensitivity;
    }

    const float keyboardOrbit = kKeyboardOrbitSpeed * deltaSeconds;
    if (input.isKeyDown(Key::ArrowLeft)) {
        m_yawDegrees -= keyboardOrbit;
    }
    if (input.isKeyDown(Key::ArrowRight)) {
        m_yawDegrees += keyboardOrbit;
    }
    if (input.isKeyDown(Key::ArrowUp)) {
        m_pitchDegrees += keyboardOrbit;
    }
    if (input.isKeyDown(Key::ArrowDown)) {
        m_pitchDegrees -= keyboardOrbit;
    }

    m_pitchDegrees = std::clamp(m_pitchDegrees, kMinimumPitch, kMaximumPitch);
    m_distance *= 1.0F - input.scrollDelta() * kZoomScale;
    m_distance = std::clamp(m_distance, kMinimumDistance, kMaximumDistance);
    applyToCamera();
}

void CameraController::applyToCamera()
{
    m_camera.setOrientation(m_yawDegrees, m_pitchDegrees);
    m_camera.setPosition(m_focusPoint - m_camera.forward() * m_distance);
}

} // namespace citybuilder
