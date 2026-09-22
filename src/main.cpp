// Adapted from the LearnOpenGL getting-started chapters through "Camera".
// The adapted sample code in this file is licensed under CC BY-NC 4.0.

#include <algorithm>
#include <cstdlib>
#include <exception>
#include <filesystem>

#include <glad/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <spdlog/spdlog.h>

#include "CityBuilder/Rendering/Shader.hpp"
#include "CityBuilder/Scene/Camera.hpp"

namespace {

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;

struct ApplicationState {
    citybuilder::Camera camera;
    int framebufferWidth = windowWidth;
    int framebufferHeight = windowHeight;
    double previousCursorX = 0.0;
    double previousCursorY = 0.0;
    bool cursorInitialised = false;
};

ApplicationState* applicationState(GLFWwindow* window)
{
    return static_cast<ApplicationState*>(glfwGetWindowUserPointer(window));
}

void framebufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    glViewport(0, 0, width, height);

    ApplicationState* state = applicationState(window);
    if (state != nullptr) {
        state->framebufferWidth = width;
        state->framebufferHeight = height;
    }
}

void cursorPositionCallback(GLFWwindow* window, const double x, const double y)
{
    ApplicationState* state = applicationState(window);
    if (state == nullptr) {
        return;
    }

    if (!state->cursorInitialised) {
        state->previousCursorX = x;
        state->previousCursorY = y;
        state->cursorInitialised = true;
        return;
    }

    const double deltaX = x - state->previousCursorX;
    const double deltaY = y - state->previousCursorY;
    state->previousCursorX = x;
    state->previousCursorY = y;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        constexpr float orbitSensitivity = 0.2F;
        state->camera.orbit(
            static_cast<float>(deltaX) * orbitSensitivity,
            static_cast<float>(-deltaY) * orbitSensitivity
        );
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
        const float panScale = state->camera.distance() * 0.0015F;
        state->camera.pan(
            static_cast<float>(-deltaX) * panScale,
            static_cast<float>(deltaY) * panScale
        );
    }
}

void scrollCallback(GLFWwindow* window, double, const double yOffset)
{
    ApplicationState* state = applicationState(window);
    if (state != nullptr) {
        state->camera.zoom(static_cast<float>(yOffset));
    }
}

void processInput(
    GLFWwindow* window,
    ApplicationState& state,
    const float deltaTime
)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    float forward = 0.0F;
    float right = 0.0F;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        forward += 1.0F;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        forward -= 1.0F;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        right += 1.0F;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        right -= 1.0F;
    }

    float movementSpeed = std::max(4.0F, state.camera.distance() * 0.75F);
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS ||
        glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
        movementSpeed *= 3.0F;
    }
    state.camera.pan(
        right * movementSpeed * deltaTime,
        forward * movementSpeed * deltaTime
    );

    constexpr float keyboardOrbitSpeed = 70.0F;
    float yaw = 0.0F;
    float pitch = 0.0F;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        yaw -= keyboardOrbitSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        yaw += keyboardOrbitSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        pitch += keyboardOrbitSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        pitch -= keyboardOrbitSpeed * deltaTime;
    }
    state.camera.orbit(yaw, pitch);
}

} // namespace

int main(const int argc, char* argv[])
{
    if (glfwInit() != GLFW_TRUE) {
        spdlog::error("Failed to initialise GLFW");
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(
        windowWidth,
        windowHeight,
        "CityBuilder - Planning Camera",
        nullptr,
        nullptr
    );
    if (window == nullptr) {
        spdlog::error("Failed to create the GLFW window");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    ApplicationState state{};
    glfwSetWindowUserPointer(window, &state);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetScrollCallback(window, scrollCallback);

    if (gladLoadGL(glfwGetProcAddress) == 0) {
        spdlog::error("Failed to initialise GLAD");
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwGetFramebufferSize(
        window,
        &state.framebufferWidth,
        &state.framebufferHeight
    );
    glViewport(0, 0, state.framebufferWidth, state.framebufferHeight);
    glEnable(GL_DEPTH_TEST);

    int result = EXIT_SUCCESS;
    try {
        const std::filesystem::path executableDirectory = argc > 0
            ? std::filesystem::absolute(argv[0]).parent_path()
            : std::filesystem::current_path();
        const std::filesystem::path assetDirectory = executableDirectory / "assets";

        citybuilder::Shader shader{
            assetDirectory / "shaders" / "ground.vert",
            assetDirectory / "shaders" / "ground.frag"
        };

        const float vertices[] = {
            -1000.0F, 0.0F, -1000.0F,
             1000.0F, 0.0F, -1000.0F,
             1000.0F, 0.0F,  1000.0F,
            -1000.0F, 0.0F,  1000.0F,
        };
        const unsigned int indices[] = {
            0, 2, 1,
            0, 3, 2,
        };

        unsigned int vertexArray = 0;
        unsigned int vertexBuffer = 0;
        unsigned int elementBuffer = 0;
        glGenVertexArrays(1, &vertexArray);
        glGenBuffers(1, &vertexBuffer);
        glGenBuffers(1, &elementBuffer);

        glBindVertexArray(vertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
        glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            sizeof(indices),
            indices,
            GL_STATIC_DRAW
        );

        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            3 * sizeof(float),
            nullptr
        );
        glEnableVertexAttribArray(0);

        double previousFrameTime = glfwGetTime();

        while (glfwWindowShouldClose(window) == GLFW_FALSE) {
            const double currentFrameTime = glfwGetTime();
            const float deltaTime = std::min(
                static_cast<float>(currentFrameTime - previousFrameTime),
                0.1F
            );
            previousFrameTime = currentFrameTime;
            processInput(window, state, deltaTime);

            glClearColor(0.075F, 0.095F, 0.105F, 1.0F);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            const int safeFramebufferHeight = std::max(
                state.framebufferHeight,
                1
            );
            const float aspectRatio = static_cast<float>(state.framebufferWidth) /
                static_cast<float>(safeFramebufferHeight);

            shader.use();
            shader.setMat4("model", glm::mat4{1.0F});
            shader.setMat4("view", state.camera.viewMatrix());
            shader.setMat4(
                "projection",
                state.camera.projectionMatrix(aspectRatio)
            );

            glBindVertexArray(vertexArray);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteVertexArrays(1, &vertexArray);
        glDeleteBuffers(1, &vertexBuffer);
        glDeleteBuffers(1, &elementBuffer);
    } catch (const std::exception& exception) {
        spdlog::error("{}", exception.what());
        result = EXIT_FAILURE;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return result;
}
