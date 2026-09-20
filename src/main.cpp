// Adapted from the LearnOpenGL "Hello Triangle", "Shaders", "Textures",
// and "Transformations" chapters.
// The adapted sample code in this file is licensed under CC BY-NC 4.0.

#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <string>

#include <glad/gl.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <spdlog/spdlog.h>
#include <stb_image.h>

#include "CityBuilder/Rendering/Shader.hpp"

namespace {

constexpr int windowWidth = 800;
constexpr int windowHeight = 600;

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

unsigned int loadTexture(const std::filesystem::path& path)
{
    int width = 0;
    int height = 0;
    int channelCount = 0;
    unsigned char* pixels = stbi_load(
        path.string().c_str(),
        &width,
        &height,
        &channelCount,
        0
    );
    if (pixels == nullptr) {
        const char* reason = stbi_failure_reason();
        throw std::runtime_error{
            "Unable to load texture " + path.string() + ": " +
            (reason != nullptr ? reason : "unknown image error")
        };
    }

    unsigned int format = 0;
    switch (channelCount) {
    case 1:
        format = GL_RED;
        break;
    case 2:
        format = GL_RG;
        break;
    case 3:
        format = GL_RGB;
        break;
    case 4:
        format = GL_RGBA;
        break;
    default:
        stbi_image_free(pixels);
        throw std::runtime_error{
            "Unsupported channel count in texture: " + path.string()
        };
    }

    unsigned int texture = 0;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        static_cast<int>(format),
        width,
        height,
        0,
        format,
        GL_UNSIGNED_BYTE,
        pixels
    );
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(pixels);
    return texture;
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
        "LearnOpenGL - Chapter 7 Transformations",
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
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (gladLoadGL(glfwGetProcAddress) == 0) {
        spdlog::error("Failed to initialise GLAD");
        glfwDestroyWindow(window);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    int framebufferWidth = 0;
    int framebufferHeight = 0;
    glfwGetFramebufferSize(window, &framebufferWidth, &framebufferHeight);
    glViewport(0, 0, framebufferWidth, framebufferHeight);

    int result = EXIT_SUCCESS;
    try {
        const std::filesystem::path executableDirectory = argc > 0
            ? std::filesystem::absolute(argv[0]).parent_path()
            : std::filesystem::current_path();
        const std::filesystem::path assetDirectory = executableDirectory / "assets";

        citybuilder::Shader shader{
            assetDirectory / "shaders" / "textured.vert",
            assetDirectory / "shaders" / "textured.frag"
        };
        shader.use();
        shader.setInt("texture1", 0);
        shader.setInt("texture2", 1);

        stbi_set_flip_vertically_on_load(true);
        const unsigned int texture1 = loadTexture(
            assetDirectory / "textures" / "container.jpg"
        );

        unsigned int texture2 = 0;
        try {
            texture2 = loadTexture(
                assetDirectory / "textures" / "awesomeface.png"
            );
        } catch (...) {
            glDeleteTextures(1, &texture1);
            throw;
        }

        const float vertices[] = {
            // position             // texture coordinate
             0.5F,  0.5F, 0.0F,    1.0F, 1.0F,
             0.5F, -0.5F, 0.0F,    1.0F, 0.0F,
            -0.5F, -0.5F, 0.0F,    0.0F, 0.0F,
            -0.5F,  0.5F, 0.0F,    0.0F, 1.0F,
        };
        const unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3,
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
            5 * sizeof(float),
            nullptr
        );
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(
            1,
            2,
            GL_FLOAT,
            GL_FALSE,
            5 * sizeof(float),
            reinterpret_cast<void*>(3 * sizeof(float))
        );
        glEnableVertexAttribArray(1);

        while (glfwWindowShouldClose(window) == GLFW_FALSE) {
            processInput(window);

            glClearColor(0.2F, 0.3F, 0.3F, 1.0F);
            glClear(GL_COLOR_BUFFER_BIT);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture1);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, texture2);

            shader.use();
            glBindVertexArray(vertexArray);

            const float elapsedTime = static_cast<float>(glfwGetTime());

            glm::mat4 transform{1.0F};
            transform = glm::translate(
                transform,
                glm::vec3{0.5F, -0.5F, 0.0F}
            );
            transform = glm::rotate(
                transform,
                elapsedTime,
                glm::vec3{0.0F, 0.0F, 1.0F}
            );
            shader.setMat4("transform", transform);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            transform = glm::mat4{1.0F};
            transform = glm::translate(
                transform,
                glm::vec3{-0.5F, 0.5F, 0.0F}
            );
            const float scale = 0.5F + 0.25F * std::sin(elapsedTime * 2.0F);
            transform = glm::scale(transform, glm::vec3{scale, scale, 1.0F});
            shader.setMat4("transform", transform);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        glDeleteTextures(1, &texture1);
        glDeleteTextures(1, &texture2);
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
