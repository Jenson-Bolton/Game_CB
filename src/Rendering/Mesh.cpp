#include "CityBuilder/Rendering/Mesh.hpp"

#include <array>
#include <cstddef>
#include <utility>

#include <glad/gl.h>

namespace citybuilder {

Mesh::Mesh(
    const std::span<const Vertex> vertices,
    const std::span<const unsigned int> indices
)
    : m_indexCount{static_cast<int>(indices.size())}
{
    glGenVertexArrays(1, &m_vertexArray);
    glGenBuffers(1, &m_vertexBuffer);
    glGenBuffers(1, &m_indexBuffer);

    glBindVertexArray(m_vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    glBufferData(
        GL_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(vertices.size_bytes()),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        static_cast<GLsizeiptr>(indices.size_bytes()),
        indices.data(),
        GL_STATIC_DRAW
    );

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<const void*>(offsetof(Vertex, position))
    );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        sizeof(Vertex),
        reinterpret_cast<const void*>(offsetof(Vertex, color))
    );
    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    release();
}

Mesh::Mesh(Mesh&& other) noexcept
    : m_vertexArray{std::exchange(other.m_vertexArray, 0)}
    , m_vertexBuffer{std::exchange(other.m_vertexBuffer, 0)}
    , m_indexBuffer{std::exchange(other.m_indexBuffer, 0)}
    , m_indexCount{std::exchange(other.m_indexCount, 0)}
{
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    if (this != &other) {
        release();
        m_vertexArray = std::exchange(other.m_vertexArray, 0);
        m_vertexBuffer = std::exchange(other.m_vertexBuffer, 0);
        m_indexBuffer = std::exchange(other.m_indexBuffer, 0);
        m_indexCount = std::exchange(other.m_indexCount, 0);
    }
    return *this;
}

Mesh Mesh::cube()
{
    constexpr std::array vertices{
        Vertex{{-1.0F, -1.0F, -1.0F}, {0.90F, 0.25F, 0.25F}},
        Vertex{{1.0F, -1.0F, -1.0F}, {0.25F, 0.80F, 0.35F}},
        Vertex{{1.0F, 1.0F, -1.0F}, {0.25F, 0.45F, 0.95F}},
        Vertex{{-1.0F, 1.0F, -1.0F}, {0.95F, 0.75F, 0.25F}},
        Vertex{{-1.0F, -1.0F, 1.0F}, {0.75F, 0.30F, 0.90F}},
        Vertex{{1.0F, -1.0F, 1.0F}, {0.20F, 0.85F, 0.85F}},
        Vertex{{1.0F, 1.0F, 1.0F}, {0.95F, 0.55F, 0.20F}},
        Vertex{{-1.0F, 1.0F, 1.0F}, {0.40F, 0.70F, 0.95F}},
    };

    constexpr std::array<unsigned int, 36> indices{
        0, 2, 1, 0, 3, 2,
        4, 5, 6, 4, 6, 7,
        0, 1, 5, 0, 5, 4,
        3, 7, 6, 3, 6, 2,
        0, 4, 7, 0, 7, 3,
        1, 2, 6, 1, 6, 5,
    };

    return Mesh{vertices, indices};
}

void Mesh::draw() const noexcept
{
    glBindVertexArray(m_vertexArray);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

void Mesh::release() noexcept
{
    if (m_indexBuffer != 0) {
        glDeleteBuffers(1, &m_indexBuffer);
    }
    if (m_vertexBuffer != 0) {
        glDeleteBuffers(1, &m_vertexBuffer);
    }
    if (m_vertexArray != 0) {
        glDeleteVertexArrays(1, &m_vertexArray);
    }
    m_indexBuffer = 0;
    m_vertexBuffer = 0;
    m_vertexArray = 0;
    m_indexCount = 0;
}

} // namespace citybuilder
