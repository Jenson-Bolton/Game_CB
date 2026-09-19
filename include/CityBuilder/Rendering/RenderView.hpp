#pragma once

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>

namespace citybuilder {

/** @brief Immutable camera data supplied to rendering systems for one frame. */
struct RenderView {
    glm::mat4 view{1.0F}; ///< World-to-view transformation.
    glm::mat4 projection{1.0F}; ///< View-to-clip transformation.
    glm::vec3 cameraPosition{}; ///< Camera position in world space.
};

} // namespace citybuilder
