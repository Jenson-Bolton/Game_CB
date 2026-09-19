#include "CityBuilder/Rendering/Shader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <spdlog/spdlog.h>

namespace citybuilder {

Shader::Shader(
    const std::filesystem::path& vertexPath,
    const std::filesystem::path& fragmentPath
)
{
    const unsigned int vertexShader = compile(GL_VERTEX_SHADER, readFile(vertexPath), vertexPath);
    const unsigned int fragmentShader = compile(GL_FRAGMENT_SHADER, readFile(fragmentPath), fragmentPath);

    m_program = glCreateProgram();
    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);
    glLinkProgram(m_program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    int linked = GL_FALSE;
    glGetProgramiv(m_program, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        int logLength = 0;
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(static_cast<std::size_t>(logLength));
        glGetProgramInfoLog(m_program, logLength, nullptr, log.data());
        glDeleteProgram(m_program);
        m_program = 0;
        throw std::runtime_error{"Shader link failed: " + std::string{log.data()}};
    }

    spdlog::debug("Loaded shaders '{}' and '{}'", vertexPath.string(), fragmentPath.string());
}

Shader::~Shader()
{
    if (m_program != 0) {
        glDeleteProgram(m_program);
    }
}

Shader::Shader(Shader&& other) noexcept
    : m_program{std::exchange(other.m_program, 0)}
{
}

Shader& Shader::operator=(Shader&& other) noexcept
{
    if (this != &other) {
        if (m_program != 0) {
            glDeleteProgram(m_program);
        }
        m_program = std::exchange(other.m_program, 0);
    }
    return *this;
}

void Shader::bind() const noexcept
{
    glUseProgram(m_program);
}

void Shader::setMat4(const char* name, const glm::mat4& value) const
{
    const int location = glGetUniformLocation(m_program, name);
    if (location < 0) {
        spdlog::warn("Shader uniform '{}' was not found", name);
        return;
    }
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
}

std::string Shader::readFile(const std::filesystem::path& path)
{
    std::ifstream stream{path};
    if (!stream) {
        throw std::runtime_error{"Unable to open shader: " + path.string()};
    }

    std::ostringstream contents;
    contents << stream.rdbuf();
    return contents.str();
}

unsigned int Shader::compile(
    const unsigned int type,
    const std::string& source,
    const std::filesystem::path& path
)
{
    const unsigned int shader = glCreateShader(type);
    const char* sourcePointer = source.c_str();
    glShaderSource(shader, 1, &sourcePointer, nullptr);
    glCompileShader(shader);

    int compiled = GL_FALSE;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        int logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::vector<char> log(static_cast<std::size_t>(logLength));
        glGetShaderInfoLog(shader, logLength, nullptr, log.data());
        glDeleteShader(shader);
        throw std::runtime_error{
            "Shader compilation failed for " + path.string() + ": " + std::string{log.data()}
        };
    }

    return shader;
}

} // namespace citybuilder
