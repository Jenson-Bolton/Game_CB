#include "CityBuilder/World/World.hpp"

#include <utility>

namespace citybuilder {

World::World(GridConfig gridConfig)
    : m_grid{std::move(gridConfig)}
{
}

void World::advance(const float deltaSeconds) noexcept
{
    m_simulationSeconds += deltaSeconds;
}

Grid& World::grid() noexcept
{
    return m_grid;
}

const Grid& World::grid() const noexcept
{
    return m_grid;
}

float World::simulationSeconds() const noexcept
{
    return m_simulationSeconds;
}

} // namespace citybuilder
