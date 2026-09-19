#include "CityBuilder/Resources/AssetLocator.hpp"

#include <utility>

namespace citybuilder {

AssetLocator::AssetLocator(std::filesystem::path assetRoot)
    : m_assetRoot{std::move(assetRoot)}
{
}

std::filesystem::path AssetLocator::shader(const std::string_view filename) const
{
    return m_assetRoot / "shaders" / filename;
}

} // namespace citybuilder
