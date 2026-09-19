#pragma once

#include <glm/vec3.hpp>

namespace citybuilder {

/** @brief Immutable dimensions and placement of a city grid. */
struct GridConfig {
    int columns{64}; ///< Number of tile columns.
    int rows{64}; ///< Number of tile rows.
    float cellSize{1.0F}; ///< Width and depth of each tile in world units.
    glm::vec3 origin{-32.0F, 0.0F, -32.0F}; ///< Minimum world-space corner.
};

} // namespace citybuilder
