#pragma once

#include <filesystem>
#include <string_view>

namespace citybuilder {

/** @brief Resolves runtime asset paths relative to the executable. */
class AssetLocator final {
public:
    /** @param assetRoot Root directory containing copied runtime assets. */
    explicit AssetLocator(std::filesystem::path assetRoot);

    /**
     * @brief Resolves a shader filename below the shader asset directory.
     * @param filename Shader filename such as "grid.vert".
     * @return Full filesystem path to the shader.
     */
    [[nodiscard]] std::filesystem::path shader(std::string_view filename) const;

private:
    std::filesystem::path m_assetRoot;
};

} // namespace citybuilder
