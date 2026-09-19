#pragma once

#include "CityBuilder/World/Grid.hpp"

namespace citybuilder {

/** @brief Owns persistent world state independently of rendering. */
class World final {
public:
    /** @brief Creates a world containing one city grid. */
    explicit World(GridConfig gridConfig);

    /** Advances world time by one fixed simulation step. */
    void advance(float deltaSeconds) noexcept;

    /** @return Mutable city grid. */
    [[nodiscard]] Grid& grid() noexcept;
    /** @return Read-only city grid. */
    [[nodiscard]] const Grid& grid() const noexcept;
    /** @return Total fixed-step simulation time in seconds. */
    [[nodiscard]] float simulationSeconds() const noexcept;

private:
    Grid m_grid;
    float m_simulationSeconds{};
};

} // namespace citybuilder
