#include "CityBuilder/Rendering/Renderer.hpp"

#include <stdexcept>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace citybuilder {
namespace {

void APIENTRY openGlDebugCallback(
    unsigned int,
    unsigned int,
    unsigned int id,
    unsigned int severity,
    int,
    const char* message,
    const void*
)
{
    if (severity == GL_DEBUG_SEVERITY_NOTIFICATION) {
        spdlog::debug("OpenGL [{}]: {}", id, message);
    } else if (severity == GL_DEBUG_SEVERITY_LOW) {
        spdlog::warn("OpenGL [{}]: {}", id, message);
    } else {
        spdlog::error("OpenGL [{}]: {}", id, message);
    }
}

const char* glString(const unsigned int name)
{
    const auto* value = glGetString(name);
    return value == nullptr ? "unknown" : reinterpret_cast<const char*>(value);
}

} // namespace

Renderer::Renderer(GLFWwindow* window)
{
    if (window == nullptr || gladLoadGL(glfwGetProcAddress) == 0) {
        throw std::runtime_error{"Unable to load OpenGL functions with GLAD"};
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

#ifndef NDEBUG
    if (GLAD_GL_KHR_debug) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(openGlDebugCallback, nullptr);
    }
#endif

    spdlog::info("OpenGL {}", glString(GL_VERSION));
    spdlog::info("GPU: {} ({})", glString(GL_RENDERER), glString(GL_VENDOR));
}

void Renderer::beginFrame(
    const int width,
    const int height,
    const glm::vec3& clearColor
) const noexcept
{
    glViewport(0, 0, width, height);
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} // namespace citybuilder
