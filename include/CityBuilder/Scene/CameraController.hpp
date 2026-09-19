#pragma once

#include <glm/vec3.hpp>

namespace citybuilder {

class Camera;
class Input;

/** @brief Implements pan, orbit, and zoom controls suited to a city builder. */
class CameraController final {
public:
    /** Attaches a controller to a camera and applies its initial orbit pose. */
    explicit CameraController(Camera& camera);

    /**
     * @brief Updates camera navigation from one rendered frame of input.
     * @param input Current keyboard and pointer state.
     * @param deltaSeconds Rendered-frame duration in seconds.
     */
    void update(const Input& input, float deltaSeconds);

private:
    void applyToCamera();

    Camera& m_camera;
    glm::vec3 m_focusPoint{};
    float m_distance{46.0F};
    float m_yawDegrees{-45.0F};
    float m_pitchDegrees{-50.0F};
};

} // namespace citybuilder
