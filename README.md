# City Builder

A C++20 and OpenGL foundation for a 3D city-building game. The current build
opens a resizable window and renders a rotating, depth-tested cube through a
small reusable rendering layer.

## Included

- GLFW 3.4 for windows, input, and the OpenGL context
- GLAD 2.0.8 with a bundled OpenGL 3.3 loader
- GLM 1.0.3 for vectors, matrices, and camera transforms
- spdlog 1.17.0 for structured diagnostics
- CMake and a Visual Studio 2022 preset
- Doxygen configuration and a Windows GitHub Actions build
- RAII wrappers for the application, window, shaders, and GPU meshes
- OpenGL debug output, depth testing, back-face culling, and resize handling
- A free-fly camera and runtime shader assets

CMake downloads GLFW, GLM, and spdlog during the first configuration. No
separate SDK installation is required for those libraries.

## Requirements

- Visual Studio 2022 with **Desktop development with C++**
- CMake 3.24 or newer
- Git
- Doxygen (optional, for API documentation)

## Build and run

From a Developer PowerShell in the repository root:

```powershell
cmake --preset vs2022
cmake --build --preset debug
.\build\bin\Debug\CityBuilder.exe
```

Alternatively, open `build/CityBuilder.sln`. `CityBuilder` is the startup
project and its debugger working directory points at the executable folder, so
the copied shader assets are found automatically.

## Controls

- `W`, `A`, `S`, `D`: move forward, left, backward, and right
- `Q`, `E`: move down and up
- Arrow keys: look around
- `Escape`: close the application

## Documentation

Generate the HTML API documentation after configuring the project:

```powershell
cmake --build build --target docs
```

Then open `build/docs/html/index.html`.

## Project layout

```text
assets/shaders/       GLSL shader source copied beside the executable
include/CityBuilder/  Public project headers
src/                  Application and rendering implementation
docs/                 Doxygen configuration
vendor/glad/          Generated OpenGL loader
.github/workflows/    Continuous integration
```

## Next milestone

Build a ground grid and mouse-to-world picking on top of this foundation, then
add tile highlighting and simple building placement.

## License

Licensed under the [MIT License](LICENSE).
