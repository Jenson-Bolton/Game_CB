#pragma once

#include <compare>

namespace citybuilder {

/** @brief Integer address of one tile in the city grid. */
struct GridCoordinate {
    int column{}; ///< Zero-based horizontal grid coordinate.
    int row{}; ///< Zero-based vertical grid coordinate.

    /** Compares coordinates lexicographically by column and then row. */
    auto operator<=>(const GridCoordinate&) const = default;
};

} // namespace citybuilder
