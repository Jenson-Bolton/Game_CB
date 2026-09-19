#pragma once

#include <glm/vec3.hpp>

struct GLFWwindow;

namespace citybuilder {

/** Initialises OpenGL and owns frame-level render state. */
class Renderer final {
public:
    /** Loads OpenGL functions and establishes the default render state. */
    explicit Renderer(GLFWwindow* window);

    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;

    /** Sets the viewport and clears colour and depth buffers for a new frame. */
    void beginFrame(int width, int height, const glm::vec3& clearColor) const noexcept;
};

} // namespace citybuilder
