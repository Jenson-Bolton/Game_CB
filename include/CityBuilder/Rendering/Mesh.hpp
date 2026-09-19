#pragma once

#include <cstdint>
#include <span>

#include "CityBuilder/Rendering/PrimitiveTopology.hpp"
#include "CityBuilder/Rendering/Vertex.hpp"

namespace citybuilder {

/** @brief Owns an OpenGL vertex array and its static vertex/index buffers. */
class Mesh final {
public:
    /** Uploads immutable mesh data using the shared Vertex layout. */
    Mesh(
        std::span<const Vertex> vertices,
        std::span<const std::uint32_t> indices,
        PrimitiveTopology topology
    );
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    /** Transfers ownership of GPU buffers. */
    Mesh(Mesh&& other) noexcept;
    /** Transfers ownership of GPU buffers. */
    Mesh& operator=(Mesh&& other) noexcept;

    /** Draws the complete indexed mesh. */
    void draw() const noexcept;

private:
    void release() noexcept;

    unsigned int m_vertexArray{};
    unsigned int m_vertexBuffer{};
    unsigned int m_indexBuffer{};
    unsigned int m_drawMode{};
    int m_indexCount{};
};

} // namespace citybuilder
