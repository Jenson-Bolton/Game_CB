#pragma once

#include "CityBuilder/Rendering/Mesh.hpp"
#include "CityBuilder/Rendering/RenderView.hpp"
#include "CityBuilder/Rendering/Shader.hpp"

namespace citybuilder {

class AssetLocator;
struct GridConfig;

/** @brief Draws a finite line grid generated from GridConfig. */
class GridRenderer final {
public:
    /** Builds static line geometry for the supplied grid dimensions. */
    GridRenderer(const AssetLocator& assets, const GridConfig& gridConfig);

    /** Draws the grid overlay for one camera view. */
    void draw(const RenderView& view) const;

private:
    Shader m_shader;
    Mesh m_mesh;
};

} // namespace citybuilder
