#pragma once

#include <filesystem>
#include <string>

#include <glm/mat4x4.hpp>

namespace citybuilder {

/** Compiled and linked OpenGL shader program. */
class Shader final {
public:
    /** Builds a shader program from vertex and fragment shader files. */
    Shader(const std::filesystem::path& vertexPath, const std::filesystem::path& fragmentPath);
    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    /** Transfers ownership of an existing shader program. */
    Shader(Shader&& other) noexcept;
    /** Transfers ownership of an existing shader program. */
    Shader& operator=(Shader&& other) noexcept;

    /** Makes this program active for subsequent draw calls. */
    void bind() const noexcept;
    /** Updates a 4x4 matrix uniform by name. */
    void setMat4(const char* name, const glm::mat4& value) const;

private:
    [[nodiscard]] static std::string readFile(const std::filesystem::path& path);
    [[nodiscard]] static unsigned int compile(
        unsigned int type,
        const std::string& source,
        const std::filesystem::path& path
    );

    unsigned int m_program{0};
};

} // namespace citybuilder
