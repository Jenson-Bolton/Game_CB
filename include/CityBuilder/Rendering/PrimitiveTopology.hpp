#pragma once

#include <cstdint>

namespace citybuilder {

/** @brief Primitive assembly modes supported by Mesh. */
enum class PrimitiveTopology : std::uint8_t {
    Triangles, ///< Each group of three indices forms a triangle.
    Lines ///< Each pair of indices forms an independent line.
};

} // namespace citybuilder
