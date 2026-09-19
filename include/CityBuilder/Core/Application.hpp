#pragma once

#include <filesystem>

#include "CityBuilder/Core/Window.hpp"
#include "CityBuilder/Rendering/Mesh.hpp"
#include "CityBuilder/Rendering/Renderer.hpp"
#include "CityBuilder/Rendering/Shader.hpp"
#include "CityBuilder/Scene/Camera.hpp"

namespace citybuilder {

/** Owns the engine-level services and runs the main loop. */
class Application final {
public:
    /** Creates the window and rendering resources located beside the executable. */
    explicit Application(const std::filesystem::path& executablePath);

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    /** Runs until the user closes the window. */
    int run();

private:
    void processInput(float deltaSeconds);

    std::filesystem::path m_assetRoot;
    Window m_window;
    Renderer m_renderer;
    Shader m_shader;
    Mesh m_cube;
    Camera m_camera;
};

} // namespace citybuilder
