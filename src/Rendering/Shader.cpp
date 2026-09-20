#include "CityBuilder/Rendering/Shader.hpp"

#include <array>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <utility>

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

namespace citybuilder {
namespace {

std::string readFile(const std::filesystem::path& path)
{
    std::ifstream file{path, std::ios::binary};
    if (!file) {
        throw std::runtime_error{"Unable to open shader file: " + path.string()};
    }

    return {
        std::istreambuf_iterator<char>{file},
        std::istreambuf_iterator<char>{}
    };
}

unsigned int compileShader(
    const unsigned int type,
    const std::string& source,
    const std::filesystem::path& path
)
{
    const unsigned int shader = glCreateShader(type);
    const char* sourcePointer = source.c_str();
    glShaderSource(shader, 1, &sourcePointer, nullptr);
    glCompileShader(shader);

    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_TRUE) {
        return shader;
    }

    std::array<char, 1024> informationLog{};
    glGetShaderInfoLog(
        shader,
        static_cast<int>(informationLog.size()),
        nullptr,
        informationLog.data()
    );
    glDeleteShader(shader);

    throw std::runtime_error{
        "Unable to compile shader " + path.string() + ":\n" +
        informationLog.data()
    };
}

unsigned int linkProgram(const unsigned int vertexShader, const unsigned int fragmentShader)
{
    const unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    int success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_TRUE) {
        return program;
    }

    std::array<char, 1024> informationLog{};
    glGetProgramInfoLog(
        program,
        static_cast<int>(informationLog.size()),
        nullptr,
        informationLog.data()
    );
    glDeleteProgram(program);

    throw std::runtime_error{
        "Unable to link shader program:\n" + std::string{informationLog.data()}
    };
}

int uniformLocation(const unsigned int program, const std::string_view name)
{
    const std::string ownedName{name};
    const int location = glGetUniformLocation(program, ownedName.c_str());
    if (location < 0) {
        throw std::runtime_error{"Shader uniform not found: " + ownedName};
    }
    return location;
}

} // namespace

Shader::Shader(
    const std::filesystem::path& vertexShaderPath,
    const std::filesystem::path& fragmentShaderPath
)
{
    const std::string vertexSource = readFile(vertexShaderPath);
    const std::string fragmentSource = readFile(fragmentShaderPath);

    const unsigned int vertexShader = compileShader(
        GL_VERTEX_SHADER,
        vertexSource,
        vertexShaderPath
    );

    unsigned int fragmentShader = 0;
    try {
        fragmentShader = compileShader(
            GL_FRAGMENT_SHADER,
            fragmentSource,
            fragmentShaderPath
        );
        m_program = linkProgram(vertexShader, fragmentShader);
    } catch (...) {
        glDeleteShader(vertexShader);
        if (fragmentShader != 0) {
            glDeleteShader(fragmentShader);
        }
        throw;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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

void Shader::use() const noexcept
{
    glUseProgram(m_program);
}

void Shader::setInt(const std::string_view name, const int value) const
{
    glUniform1i(uniformLocation(m_program, name), value);
}

void Shader::setMat4(const std::string_view name, const glm::mat4& value) const
{
    glUniformMatrix4fv(
        uniformLocation(m_program, name),
        1,
        GL_FALSE,
        glm::value_ptr(value)
    );
}

} // namespace citybuilder
