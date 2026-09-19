#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace citybuilder {

class Window;

/** Lightweight free-fly camera for exploring the scene. */
class Camera final {
public:
    /** Creates a perspective camera at the supplied world position. */
    explicit Camera(glm::vec3 position = {0.0F, 2.5F, 6.0F});

    /** Applies keyboard movement and look controls for one frame. */
    void update(const Window& window, float deltaSeconds);

    /** Returns the world-to-view transform. */
    [[nodiscard]] glm::mat4 viewMatrix() const;
    /** Returns a perspective projection for the supplied viewport aspect ratio. */
    [[nodiscard]] glm::mat4 projectionMatrix(float aspectRatio) const;

private:
    [[nodiscard]] glm::vec3 forward() const;

    glm::vec3 m_position;
    float m_yawDegrees{-90.0F};
    float m_pitchDegrees{-15.0F};
};

} // namespace citybuilder
