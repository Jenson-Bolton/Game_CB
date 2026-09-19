#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace citybuilder {

/** @brief Perspective camera state with no dependency on input or window APIs. */
class Camera final {
public:
    /** Creates a perspective camera at the supplied world position. */
    explicit Camera(glm::vec3 position = {0.0F, 12.0F, 14.0F});

    /** Sets the camera's world-space position. */
    void setPosition(glm::vec3 position) noexcept;
    /** Sets yaw and pitch in degrees, clamping pitch away from singularities. */
    void setOrientation(float yawDegrees, float pitchDegrees) noexcept;
    /** Sets the vertical perspective field of view in degrees. */
    void setFieldOfView(float fieldOfViewDegrees) noexcept;

    /** @return Camera position in world space. */
    [[nodiscard]] const glm::vec3& position() const noexcept;
    /** @return Normalised direction in which the camera is looking. */
    [[nodiscard]] glm::vec3 forward() const;
    /** @return Normalised camera-right direction. */
    [[nodiscard]] glm::vec3 right() const;
    /** @return World-to-view transformation. */
    [[nodiscard]] glm::mat4 viewMatrix() const;
    /** @return Perspective projection for the supplied viewport aspect ratio. */
    [[nodiscard]] glm::mat4 projectionMatrix(float aspectRatio) const;

private:
    glm::vec3 m_position;
    float m_yawDegrees{-45.0F};
    float m_pitchDegrees{-50.0F};
    float m_fieldOfViewDegrees{55.0F};
};

} // namespace citybuilder
