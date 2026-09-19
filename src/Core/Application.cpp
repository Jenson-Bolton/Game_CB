#include "CityBuilder/Core/Application.hpp"

#include <glm/vec3.hpp>
#include <spdlog/spdlog.h>

#include "CityBuilder/Rendering/RenderView.hpp"

namespace citybuilder {
namespace {

constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;
constexpr glm::vec3 kClearColor{0.07F, 0.10F, 0.15F};

} // namespace

Application::Application(const std::filesystem::path& executablePath)
    : m_window{kWindowWidth, kWindowHeight, "City Builder"}
    , m_renderer{m_window.nativeHandle()}
    , m_assets{executablePath.parent_path() / "assets"}
    , m_clock{}
    , m_world{GridConfig{}}
    , m_camera{}
    , m_cameraController{m_camera}
    , m_worldRenderer{m_assets, m_world.grid().config()}
{
    spdlog::info(
        "Created {}x{} city grid",
        m_world.grid().config().columns,
        m_world.grid().config().rows
    );
}

int Application::run()
{
    while (!m_window.shouldClose()) {
        Input& input = m_window.input();
        input.beginFrame();
        m_window.pollEvents();
        m_clock.tick();

        processInput();
        m_cameraController.update(input, m_clock.frameDeltaSeconds());

        while (m_clock.consumeFixedStep()) {
            m_world.advance(m_clock.fixedDeltaSeconds());
        }

        const auto [width, height] = m_window.framebufferSize();
        if (width <= 0 || height <= 0) {
            continue;
        }

        const float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        const RenderView view{
            .view = m_camera.viewMatrix(),
            .projection = m_camera.projectionMatrix(aspectRatio),
            .cameraPosition = m_camera.position(),
        };

        m_renderer.beginFrame(width, height, kClearColor);
        m_worldRenderer.render(view);
        m_window.swapBuffers();
    }

    spdlog::info("City Builder shut down cleanly");
    return 0;
}

void Application::processInput()
{
    if (m_window.input().wasKeyPressed(Key::Escape)) {
        m_window.requestClose();
    }
}

} // namespace citybuilder
