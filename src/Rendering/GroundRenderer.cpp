#include "CityBuilder/Rendering/GroundRenderer.hpp"

#include <array>
#include <cstdint>

#include "CityBuilder/Resources/AssetLocator.hpp"
#include "CityBuilder/World/GridConfig.hpp"

namespace citybuilder {
namespace {

[[nodiscard]] Mesh makeGroundMesh(const GridConfig& config)
{
    const float minimumX = config.origin.x;
    const float minimumZ = config.origin.z;
    const float maximumX = minimumX + static_cast<float>(config.columns) * config.cellSize;
    const float maximumZ = minimumZ + static_cast<float>(config.rows) * config.cellSize;
    constexpr glm::vec3 color{0.14F, 0.28F, 0.18F};

    const std::array vertices{
        Vertex{{minimumX, config.origin.y, minimumZ}, {0.0F, 1.0F, 0.0F}, color, {0.0F, 0.0F}},
        Vertex{{maximumX, config.origin.y, minimumZ}, {0.0F, 1.0F, 0.0F}, color, {1.0F, 0.0F}},
        Vertex{{maximumX, config.origin.y, maximumZ}, {0.0F, 1.0F, 0.0F}, color, {1.0F, 1.0F}},
        Vertex{{minimumX, config.origin.y, maximumZ}, {0.0F, 1.0F, 0.0F}, color, {0.0F, 1.0F}},
    };
    constexpr std::array<std::uint32_t, 6> indices{0, 2, 1, 0, 3, 2};
    return Mesh{vertices, indices, PrimitiveTopology::Triangles};
}

} // namespace

GroundRenderer::GroundRenderer(const AssetLocator& assets, const GridConfig& gridConfig)
    : m_shader{assets.shader("ground.vert"), assets.shader("ground.frag")}
    , m_mesh{makeGroundMesh(gridConfig)}
{
}

void GroundRenderer::draw(const RenderView& view) const
{
    m_shader.bind();
    m_shader.setMat4("uView", view.view);
    m_shader.setMat4("uProjection", view.projection);
    m_mesh.draw();
}

} // namespace citybuilder
