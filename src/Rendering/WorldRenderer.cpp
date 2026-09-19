#include "CityBuilder/Rendering/WorldRenderer.hpp"

#include "CityBuilder/Resources/AssetLocator.hpp"
#include "CityBuilder/World/GridConfig.hpp"

namespace citybuilder {

WorldRenderer::WorldRenderer(const AssetLocator& assets, const GridConfig& gridConfig)
    : m_groundRenderer{assets, gridConfig}
    , m_gridRenderer{assets, gridConfig}
{
}

void WorldRenderer::render(const RenderView& view) const
{
    m_groundRenderer.draw(view);
    m_gridRenderer.draw(view);
}

} // namespace citybuilder
