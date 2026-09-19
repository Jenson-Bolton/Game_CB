#include "CityBuilder/World/Grid.hpp"

#include <cmath>
#include <stdexcept>
#include <utility>

namespace citybuilder {

Grid::Grid(GridConfig config)
    : m_config{std::move(config)}
{
    if (m_config.columns <= 0 || m_config.rows <= 0 || m_config.cellSize <= 0.0F) {
        throw std::invalid_argument{"Grid dimensions and cell size must be positive"};
    }

    const auto tileCount = static_cast<std::size_t>(m_config.columns)
        * static_cast<std::size_t>(m_config.rows);
    m_tiles.resize(tileCount);
}

const GridConfig& Grid::config() const noexcept
{
    return m_config;
}

bool Grid::contains(const GridCoordinate coordinate) const noexcept
{
    return coordinate.column >= 0 && coordinate.column < m_config.columns
        && coordinate.row >= 0 && coordinate.row < m_config.rows;
}

Tile& Grid::at(const GridCoordinate coordinate)
{
    return m_tiles.at(index(coordinate));
}

const Tile& Grid::at(const GridCoordinate coordinate) const
{
    return m_tiles.at(index(coordinate));
}

glm::vec3 Grid::tileCentre(const GridCoordinate coordinate) const
{
    const Tile& tile = at(coordinate);
    return {
        m_config.origin.x + (static_cast<float>(coordinate.column) + 0.5F) * m_config.cellSize,
        m_config.origin.y + tile.elevation,
        m_config.origin.z + (static_cast<float>(coordinate.row) + 0.5F) * m_config.cellSize,
    };
}

std::optional<GridCoordinate> Grid::coordinateAt(const glm::vec3 worldPosition) const
{
    const float localX = worldPosition.x - m_config.origin.x;
    const float localZ = worldPosition.z - m_config.origin.z;
    const GridCoordinate coordinate{
        static_cast<int>(std::floor(localX / m_config.cellSize)),
        static_cast<int>(std::floor(localZ / m_config.cellSize)),
    };
    return contains(coordinate) ? std::optional<GridCoordinate>{coordinate} : std::nullopt;
}

std::size_t Grid::index(const GridCoordinate coordinate) const
{
    if (!contains(coordinate)) {
        throw std::out_of_range{"Grid coordinate lies outside the grid"};
    }

    return static_cast<std::size_t>(coordinate.row)
        * static_cast<std::size_t>(m_config.columns)
        + static_cast<std::size_t>(coordinate.column);
}

} // namespace citybuilder
