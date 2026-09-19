#pragma once

#include <span>

#include <glm/vec3.hpp>

namespace citybuilder {

/** Vertex/index buffer collection with a fixed position-and-colour layout. */
class Mesh final {
public:
    ~Mesh();

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    /** Transfers ownership of GPU buffers. */
    Mesh(Mesh&& other) noexcept;
    /** Transfers ownership of GPU buffers. */
    Mesh& operator=(Mesh&& other) noexcept;

    /** Creates the foundation's depth-tested demonstration cube. */
    [[nodiscard]] static Mesh cube();

    /** Draws the mesh using its index buffer. */
    void draw() const noexcept;

private:
    struct Vertex {
        glm::vec3 position;
        glm::vec3 color;
    };

    Mesh(std::span<const Vertex> vertices, std::span<const unsigned int> indices);
    void release() noexcept;

    unsigned int m_vertexArray{0};
    unsigned int m_vertexBuffer{0};
    unsigned int m_indexBuffer{0};
    int m_indexCount{0};
};

} // namespace citybuilder
