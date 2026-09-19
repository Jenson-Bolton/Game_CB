#include <cstdlib>

#define GLFW_INCLUDE_NONE
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <spdlog/spdlog.h>

namespace {

constexpr int kWindowWidth = 1280;
constexpr int kWindowHeight = 720;
constexpr const char* kWindowTitle = "City Builder";
constexpr glm::vec3 kClearColor{0.08F, 0.12F, 0.18F};

void glfwErrorCallback(const int error, const char* description)
{
    spdlog::error("GLFW error {}: {}", error, description);
}

void framebufferSizeCallback(GLFWwindow*, const int width, const int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

} // namespace

/**
 * @brief Starts the application and runs the main render loop.
 * @return EXIT_SUCCESS on a clean shutdown, otherwise EXIT_FAILURE.
 */
int main()
{
    spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Starting City Builder");

    glfwSetErrorCallback(glfwErrorCallback);

    if (glfwInit() != GLFW_TRUE) {
        spdlog::critical("Unable to initialise GLFW");
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        kWindowWidth,
        kWindowHeight,
        kWindowTitle,
        nullptr,
        nullptr
    );

    if (window == nullptr) {
        spdlog::critical("Unable to create the application window");
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    const int openGlVersion = gladLoadGL(glfwGetProcAddress);
    if (openGlVersion == 0) {
        spdlog::critical("Unable to load OpenGL functions with GLAD");
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    spdlog::info(
        "Loaded OpenGL {}.{}",
        GLAD_VERSION_MAJOR(openGlVersion),
        GLAD_VERSION_MINOR(openGlVersion)
    );

    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    int framebufferWidth = 0;
    int framebufferHeight = 0;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);

    while (glfwWindowShouldClose(window) == GLFW_FALSE) {
        processInput(window);

        glClearColor(kClearColor.r, kClearColor.g, kClearColor.b, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    spdlog::info("City Builder shut down cleanly");
    return EXIT_SUCCESS;
}
