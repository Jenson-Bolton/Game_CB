#include "CityBuilder/Rendering/GridRenderer.hpp"

#include <cstdint>
#include <vector>

#include "CityBuilder/Resources/AssetLocator.hpp"
#include "CityBuilder/World/GridConfig.hpp"

namespace citybuilder {
namespace {

[[nodiscard]] glm::vec3 lineColor(const int line)
{
    return line % 8 == 0 ? glm::vec3{0.48F, 0.58F, 0.52F} : glm::vec3{0.28F, 0.38F, 0.32F};
}

void addLine(
    std::vector<Vertex>& vertices,
    std::vector<std::uint32_t>& indices,
    const glm::vec3 start,
    const glm::vec3 end,
    const glm::vec3 color
)
{
    const auto firstIndex = static_cast<std::uint32_t>(vertices.size());
    vertices.push_back(Vertex{start, {0.0F, 1.0F, 0.0F}, color, {0.0F, 0.0F}});
    vertices.push_back(Vertex{end, {0.0F, 1.0F, 0.0F}, color, {1.0F, 0.0F}});
    indices.push_back(firstIndex);
    indices.push_back(firstIndex + 1U);
}

[[nodiscard]] Mesh makeGridMesh(const GridConfig& config)
{
    constexpr float kGridHeightOffset = 0.002F;
    const float y = config.origin.y + kGridHeightOffset;
    const float minimumX = config.origin.x;
    const float minimumZ = config.origin.z;
    const float maximumX = minimumX + static_cast<float>(config.columns) * config.cellSize;
    const float maximumZ = minimumZ + static_cast<float>(config.rows) * config.cellSize;

    std::vector<Vertex> vertices;
    std::vector<std::uint32_t> indices;
    const std::size_t lineCount = static_cast<std::size_t>(config.columns + config.rows + 2);
    vertices.reserve(lineCount * 2U);
    indices.reserve(lineCount * 2U);

    for (int column = 0; column <= config.columns; ++column) {
        const float x = minimumX + static_cast<float>(column) * config.cellSize;
        addLine(vertices, indices, {x, y, minimumZ}, {x, y, maximumZ}, lineColor(column));
    }
    for (int row = 0; row <= config.rows; ++row) {
        const float z = minimumZ + static_cast<float>(row) * config.cellSize;
        addLine(vertices, indices, {minimumX, y, z}, {maximumX, y, z}, lineColor(row));
    }

    return Mesh{vertices, indices, PrimitiveTopology::Lines};
}

} // namespace

GridRenderer::GridRenderer(const AssetLocator& assets, const GridConfig& gridConfig)
    : m_shader{assets.shader("grid.vert"), assets.shader("grid.frag")}
    , m_mesh{makeGridMesh(gridConfig)}
{
}

void GridRenderer::draw(const RenderView& view) const
{
    m_shader.bind();
    m_shader.setMat4("uView", view.view);
    m_shader.setMat4("uProjection", view.projection);
    m_mesh.draw();
}

} // namespace citybuilder
