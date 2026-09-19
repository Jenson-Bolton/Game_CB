#pragma once

#include <filesystem>

#include "CityBuilder/Core/GameClock.hpp"
#include "CityBuilder/Core/Window.hpp"
#include "CityBuilder/Rendering/Renderer.hpp"
#include "CityBuilder/Rendering/WorldRenderer.hpp"
#include "CityBuilder/Resources/AssetLocator.hpp"
#include "CityBuilder/Scene/Camera.hpp"
#include "CityBuilder/Scene/CameraController.hpp"
#include "CityBuilder/World/World.hpp"

namespace citybuilder {

/** @brief Composition root that owns engine services and coordinates the game loop. */
class Application final {
public:
    /** Creates engine services and runtime resources located beside the executable. */
    explicit Application(const std::filesystem::path& executablePath);

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    /** Runs the application until its window is closed. */
    int run();

private:
    void processInput();

    Window m_window;
    Renderer m_renderer;
    AssetLocator m_assets;
    GameClock m_clock;
    World m_world;
    Camera m_camera;
    CameraController m_cameraController;
    WorldRenderer m_worldRenderer;
};

} // namespace citybuilder
