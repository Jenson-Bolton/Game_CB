#pragma once

#include <GLFW/glfw3.h>

#include "CityBuilder/Scene/Camera.hpp"

namespace citybuilder {

class Application {
  public:
    Application();
    ~Application();

    int run();

  private:
    void processInputs();
    void update();
    void render(float alpha);

    GLFWwindow* m_window;
    Camera m_camera;
    // CameraController m_cameraController;
};

} // namespace citybuilder

