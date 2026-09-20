#pragma once

#include <filesystem>
#include <string_view>

#include <glm/mat4x4.hpp>

namespace citybuilder {

class Shader final {
public:
    Shader(
        const std::filesystem::path& vertexShaderPath,
        const std::filesystem::path& fragmentShaderPath
    );
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other) noexcept;
    Shader& operator=(Shader&& other) noexcept;

    void use() const noexcept;
    void setInt(std::string_view name, int value) const;
    void setMat4(std::string_view name, const glm::mat4& value) const;

private:
    unsigned int m_program = 0;
};

} // namespace citybuilder
