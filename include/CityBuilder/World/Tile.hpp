#pragma once

#include <cstdint>

namespace citybuilder {

/** @brief Basic terrain classifications used by the world grid. */
enum class TerrainType : std::uint8_t {
    Grass, ///< Buildable grassy terrain.
    Water, ///< Non-buildable water terrain.
    Rock ///< Non-buildable rocky terrain.
};

/** @brief Passive simulation data stored for a single grid cell. */
struct Tile {
    TerrainType terrain{TerrainType::Grass}; ///< Terrain classification.
    float elevation{}; ///< Surface height above the grid origin.
    bool buildable{true}; ///< Whether construction is permitted.
};

} // namespace citybuilder
