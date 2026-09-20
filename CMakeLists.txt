cmake_minimum_required(VERSION 3.24)

project(CityBuilder
    VERSION 0.1.0
    DESCRIPTION "A 3D city builder built with C++ and OpenGL"
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW TRUE
)

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
    GIT_SHALLOW TRUE
)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.17.0
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glfw glm spdlog)

add_library(glad STATIC vendor/glad/src/gl.c)
target_include_directories(glad PUBLIC vendor/glad/include)

add_library(stb_image STATIC src/ThirdParty/stb_image.cpp)
target_include_directories(stb_image PUBLIC vendor/stb)

find_package(OpenGL REQUIRED)

set(CITY_BUILDER_SOURCES
    src/main.cpp
    src/Rendering/Shader.cpp
)

set(CITY_BUILDER_HEADERS
    include/CityBuilder/Rendering/Shader.hpp
)

add_executable(CityBuilder ${CITY_BUILDER_SOURCES} ${CITY_BUILDER_HEADERS})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${CITY_BUILDER_SOURCES} ${CITY_BUILDER_HEADERS})

target_include_directories(CityBuilder PRIVATE include)

target_link_libraries(CityBuilder PRIVATE
    glfw
    glad
    stb_image
    glm::glm
    spdlog::spdlog
    OpenGL::GL
)

if(MSVC)
    target_compile_options(CityBuilder PRIVATE /W4 /permissive- /Zc:__cplusplus)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CityBuilder)
else()
    target_compile_options(CityBuilder PRIVATE -Wall -Wextra -Wpedantic)
endif()

set_target_properties(CityBuilder PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:CityBuilder>"
)

add_custom_command(TARGET CityBuilder POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:CityBuilder>/assets"
    COMMENT "Copying runtime assets"
)

find_package(Doxygen)
if(Doxygen_FOUND)
    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    add_custom_target(docs
        COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()
