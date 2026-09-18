# City Builder

A starter project for a 3D city builder made with C++20, OpenGL, and GLFW.
It currently opens a resizable 1280×720 OpenGL window with a dark background.
Press **Escape** or close the window to exit.

The project uses GLAD to load modern OpenGL functions and GLM for graphics
math. GLAD's generated OpenGL 3.3 loader is included in the repository; CMake
downloads GLFW and GLM during configuration, so no manual SDK setup is required.

## Requirements

- Visual Studio 2022 with **Desktop development with C++**
- CMake 3.24 or newer
- Git
- Doxygen (optional, for API documentation)

GLFW 3.4 and GLM 1.0.3 are downloaded automatically by CMake during the first
configuration. The bundled loader was generated with GLAD 2.0.8.

## Build and run

From a Developer PowerShell in the repository root:

```powershell
cmake --preset vs2022
cmake --build --preset debug
.\build\bin\Debug\CityBuilder.exe
```

Or open `build/CityBuilder.sln` in Visual Studio after running the first command.
`CityBuilder` is configured as the startup project.

## Documentation

Generate the HTML documentation after configuring the project:

```powershell
cmake --build build --target docs
```

Then open `build/docs/html/index.html`.

## Project layout

```text
src/                 Application source code
docs/                Doxygen configuration
.github/workflows/   Continuous integration
CMakeLists.txt        Build definition
CMakePresets.json     Visual Studio build presets
```

## Next steps

Good early milestones are camera controls, shader management, a grid renderer,
and an entity/component model for buildings and roads.

## License

Licensed under the [MIT License](LICENSE).
