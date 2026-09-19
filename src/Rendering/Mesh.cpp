#include "CityBuilder/Rendering/Mesh.hpp"

#include <cstddef>
#include <stdexcept>
#include <utility>

#include <glad/gl.h>

namespace citybuilder {
namespace {

[[nodiscard]] unsigned int openGlMode(const PrimitiveTopology topology)
{
    switch (topology) {
    case PrimitiveTopology::Triangles:
        return GL_TRIANGLES;
    case PrimitiveTopology::Lines:
        return GL_LINES;
    }
    throw std::invalid_argument{"Unsupported primitive topology"};
}

} // namespace

Mesh::Mesh(
    const std::span<const Vertex> vertices,
    const std::span<const std::uint32_t> indices,
    const PrimitiveTopology topology
)
    : m_drawMode{openGlMode(topology)}
    , m_indexCount{static_cast<int>(indices.size())}
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
        0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        reinterpret_cast<const void*>(offsetof(Vertex, position))
    );
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        reinterpret_cast<const void*>(offsetof(Vertex, normal))
    );
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(
        2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        reinterpret_cast<const void*>(offsetof(Vertex, color))
    );
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(
        3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
        reinterpret_cast<const void*>(offsetof(Vertex, textureCoordinate))
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
    , m_drawMode{std::exchange(other.m_drawMode, 0)}
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
        m_drawMode = std::exchange(other.m_drawMode, 0);
        m_indexCount = std::exchange(other.m_indexCount, 0);
    }
    return *this;
}

void Mesh::draw() const noexcept
{
    glBindVertexArray(m_vertexArray);
    glDrawElements(m_drawMode, m_indexCount, GL_UNSIGNED_INT, nullptr);
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
    m_vertexArray = 0;
    m_vertexBuffer = 0;
    m_indexBuffer = 0;
    m_drawMode = 0;
    m_indexCount = 0;
}

} // namespace citybuilder
