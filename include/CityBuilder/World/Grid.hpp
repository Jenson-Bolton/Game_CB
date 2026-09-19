#pragma once

#include <cstddef>
#include <optional>
#include <vector>

#include <glm/vec3.hpp>

#include "CityBuilder/World/GridConfig.hpp"
#include "CityBuilder/World/GridCoordinate.hpp"
#include "CityBuilder/World/Tile.hpp"

namespace citybuilder {

/** @brief Owns contiguous tile data and grid/world coordinate conversions. */
class Grid final {
public:
    /** @brief Creates a grid and validates that its dimensions are positive. */
    explicit Grid(GridConfig config);

    /** @return Grid dimensions, cell size, and world origin. */
    [[nodiscard]] const GridConfig& config() const noexcept;
    /** @return True when the coordinate lies inside the grid. */
    [[nodiscard]] bool contains(GridCoordinate coordinate) const noexcept;

    /** @return Mutable tile at the coordinate. @throws std::out_of_range outside the grid. */
    [[nodiscard]] Tile& at(GridCoordinate coordinate);
    /** @return Tile at the coordinate. @throws std::out_of_range outside the grid. */
    [[nodiscard]] const Tile& at(GridCoordinate coordinate) const;

    /** @return World-space centre of the requested tile, including elevation. */
    [[nodiscard]] glm::vec3 tileCentre(GridCoordinate coordinate) const;
    /** @return Grid coordinate under a world position, or no value outside the grid. */
    [[nodiscard]] std::optional<GridCoordinate> coordinateAt(glm::vec3 worldPosition) const;

private:
    [[nodiscard]] std::size_t index(GridCoordinate coordinate) const;

    GridConfig m_config;
    std::vector<Tile> m_tiles;
};

} // namespace citybuilder
