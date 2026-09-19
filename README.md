# City Builder

A C++20 and OpenGL foundation for a 3D city-building game. The current build
opens a resizable window, renders a finite 64x64 city grid, and provides
city-builder pan, orbit, and zoom controls.

## Included

- GLFW 3.4 for windows, input, and the OpenGL context
- GLAD 2.0.8 with a bundled OpenGL 3.3 loader
- GLM 1.0.3 for vectors, matrices, and camera transforms
- spdlog 1.17.0 for structured diagnostics
- CMake and a Visual Studio 2022 preset
- Doxygen configuration and a Windows GitHub Actions build
- RAII wrappers for the application, window, shaders, and GPU meshes
- OpenGL debug output, depth testing, back-face culling, and resize handling
- A fixed-rate 60 Hz world clock with frame-rate-independent navigation
- Passive, contiguous world-grid and tile data with coordinate conversion
- A city-builder camera with keyboard pan, mouse pan/orbit, and wheel zoom
- Separate ground, grid, and world rendering components
- A small runtime asset locator and copied GLSL shader assets

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

- `W`, `A`, `S`, `D`: pan across the ground
- Middle-mouse drag: pan across the ground
- Right-mouse drag: orbit around the focus point
- Mouse wheel: zoom
- Arrow keys: keyboard orbit controls
- `Escape`: close the application

The input layer targets an ANSI 60% keyboard. Logical arrow keys and F1-F12
are supported when the keyboard firmware emits them through its Fn layer. The
physical Fn modifier itself is handled inside the keyboard and is not exposed
to GLFW or the operating system.

## Documentation

Generate the HTML API documentation after configuring the project:

```powershell
cmake --build build --target docs
```

Then open `build/docs/html/index.html`.

## Project layout

```text
assets/shaders/       Ground, grid, and reusable GLSL shaders
include/CityBuilder/  Core, resources, rendering, scene, and world interfaces
src/                  Mirrored subsystem implementations
docs/                 Doxygen configuration
vendor/glad/          Generated OpenGL loader
.github/workflows/    Continuous integration
```

## Next milestone

Add mouse-to-world ray casting, tile highlighting, and simple building
placement on top of the grid coordinate conversions.

## License

Licensed under the [MIT License](LICENSE).
