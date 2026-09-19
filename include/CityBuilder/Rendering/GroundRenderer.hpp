#pragma once

#include "CityBuilder/Rendering/Mesh.hpp"
#include "CityBuilder/Rendering/RenderView.hpp"
#include "CityBuilder/Rendering/Shader.hpp"

namespace citybuilder {

class AssetLocator;
struct GridConfig;

/** @brief Draws the solid ground surface below the city grid. */
class GroundRenderer final {
public:
    /** Builds a ground mesh matching the supplied grid dimensions. */
    GroundRenderer(const AssetLocator& assets, const GridConfig& gridConfig);

    /** Draws the ground for one camera view. */
    void draw(const RenderView& view) const;

private:
    Shader m_shader;
    Mesh m_mesh;
};

} // namespace citybuilder
