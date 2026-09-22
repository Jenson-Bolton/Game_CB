#include "CityBuilder/Core/Application.hpp"

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>
#include <chrono>

namespace citybuilder {

Application::Application()
{
    // ----- Get application config -----



    // ----- Construct window and OpenGL -----



    // ----- Construct renderer -----



    // ----- Construct camera and controller -----



    // ----- Construct world system -----



    // ----- Set initial render and sim config -----



}

Application::~Application() {}

int Application::run()
{
    const std::chrono::microseconds US_PER_UPDATE(16666);
    const std::chrono::microseconds MAX_FRAME_TIME = US_PER_UPDATE * 5;

    std::chrono::time_point<std::chrono::steady_clock> previousTime =
        std::chrono::steady_clock::now();
    std::chrono::microseconds lag(0);

    while (!glfwWindowShouldClose(m_window)) {
        std::chrono::time_point<std::chrono::steady_clock> currentTime =
            std::chrono::steady_clock::now();

        std::chrono::microseconds elapsedTime =
            std::chrono::duration_cast<std::chrono::microseconds>(currentTime - previousTime);
        previousTime = currentTime;

        // Spiral Protection
        if (elapsedTime > MAX_FRAME_TIME) {
            float elapsedMs = std::chrono::duration<float, std::milli>(elapsedTime).count();
            float maxMs = std::chrono::duration<float, std::milli>(MAX_FRAME_TIME).count();

            spdlog::warn("Frame spike detected! Elapsed: {:.2f}ms exceeds maximum limit: {:.2f}ms. "
                         "Clamping timestep.",
                         elapsedMs, maxMs);

            elapsedTime = MAX_FRAME_TIME;

        }

        lag += elapsedTime;

        processInputs();

        while (lag >= US_PER_UPDATE) {
            update();
            lag -= US_PER_UPDATE;
        }

        float alpha =
            std::chrono::duration<float>(lag) / std::chrono::duration<float>(US_PER_UPDATE);
        render(alpha);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    return 0;
}

void Application::processInputs() {}

void Application::update() {}

void Application::render(float alpha) {}

} // namespace citybuilder
