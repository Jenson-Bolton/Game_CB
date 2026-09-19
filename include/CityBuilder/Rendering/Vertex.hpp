#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace citybuilder {

/** @brief Shared static-mesh vertex format used by the Step 2 renderers. */
struct Vertex {
    glm::vec3 position{}; ///< World or model-space position.
    glm::vec3 normal{0.0F, 1.0F, 0.0F}; ///< Surface normal.
    glm::vec3 color{1.0F}; ///< Linear vertex colour.
    glm::vec2 textureCoordinate{}; ///< Texture coordinate reserved for later materials.
};

} // namespace citybuilder
