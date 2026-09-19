#include "CityBuilder/Core/Application.hpp"

#include <algorithm>
#include <chrono>

#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <spdlog/spdlog.h>

namespace citybuilder {
namespace {

constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;
constexpr glm::vec3 kClearColor{0.08F, 0.12F, 0.18F};

} // namespace

Application::Application(const std::filesystem::path& executablePath)
    : m_assetRoot{executablePath.parent_path() / "assets"}
    , m_window{kWindowWidth, kWindowHeight, "City Builder"}
    , m_renderer{m_window.nativeHandle()}
    , m_shader{m_assetRoot / "shaders" / "basic.vert", m_assetRoot / "shaders" / "basic.frag"}
    , m_cube{Mesh::cube()}
    , m_camera{}
{
    spdlog::info("Rendering foundation initialised");
}

int Application::run()
{
    using Clock = std::chrono::steady_clock;
    auto previousFrame = Clock::now();
    float elapsedSeconds = 0.0F;

    while (!m_window.shouldClose()) {
        const auto now = Clock::now();
        const float deltaSeconds = std::min(
            std::chrono::duration<float>(now - previousFrame).count(),
            0.1F
        );
        previousFrame = now;
        elapsedSeconds += deltaSeconds;

        m_window.pollEvents();
        processInput(deltaSeconds);

        const auto [width, height] = m_window.framebufferSize();
        if (width <= 0 || height <= 0) {
            continue;
        }

        m_renderer.beginFrame(width, height, kClearColor);

        const glm::mat4 model = glm::rotate(
            glm::mat4{1.0F},
            elapsedSeconds * 0.45F,
            glm::vec3{0.0F, 1.0F, 0.0F}
        );

        m_shader.bind();
        m_shader.setMat4("uModel", model);
        m_shader.setMat4("uView", m_camera.viewMatrix());
        m_shader.setMat4(
            "uProjection",
            m_camera.projectionMatrix(static_cast<float>(width) / static_cast<float>(height))
        );
        m_cube.draw();

        m_window.swapBuffers();
    }

    spdlog::info("City Builder shut down cleanly");
    return 0;
}

void Application::processInput(const float deltaSeconds)
{
    if (m_window.isKeyPressed(GLFW_KEY_ESCAPE)) {
        m_window.requestClose();
    }

    m_camera.update(m_window, deltaSeconds);
}

} // namespace citybuilder
