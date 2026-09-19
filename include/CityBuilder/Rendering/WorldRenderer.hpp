#pragma once

#include "CityBuilder/Rendering/GridRenderer.hpp"
#include "CityBuilder/Rendering/GroundRenderer.hpp"
#include "CityBuilder/Rendering/RenderView.hpp"

namespace citybuilder {

class AssetLocator;
struct GridConfig;

/** @brief Rendering façade for the visible city world. */
class WorldRenderer final {
public:
    /** Creates all static world rendering resources. */
    WorldRenderer(const AssetLocator& assets, const GridConfig& gridConfig);

    /** Draws opaque ground followed by the grid overlay. */
    void render(const RenderView& view) const;

private:
    GroundRenderer m_groundRenderer;
    GridRenderer m_gridRenderer;
};

} // namespace citybuilder
