# City Builder

A gridless city-planning and parcel simulation in which the player shapes how a
city develops rather than placing most buildings directly.

The game combines Japanese-style zoning with a Czech-style cadastral overlay.
The player establishes roads, zones land, and sets planning restrictions;
residents, companies, and government bodies then compete for land, subdivide
parcels, commission construction, and change the visible cadastre over time.

## Game direction

The central experience is planning and observing the consequences of policy.
Land should evolve through a connected process:

1. The player reveals terrain and connects it to external infrastructure.
2. Roads and other enabling infrastructure make land accessible.
3. Parcels receive zoning and restrictions such as height limits, floor-area
   ratios, setbacks, and noise limits.
4. People, companies, and government bodies bid for suitable land.
5. Successful owners may subdivide parcels and choose viable uses.
6. Developers procure materials and services through contracts.
7. Construction changes the city and is reflected in the cadastral view.

The intended simulation includes:

- Emergent development instead of direct building placement
- Irregular, gridless parcels and road layouts
- Land ownership, subdivision, valuation, and bidding
- Developer and government competition
- Construction supply chains, logistics, and contracts
- Public, private, and mixed service provision
- Simplified UK-style local-government income and expenditure
- Terrain initially composed primarily of field and forest parcels

The project draws inspiration from *Cities: Skylines*, *Townscaper*, *Tiny
Glade*, *Manor Lords*, and James Simo's procedural city-development work.

## Current state

The implementation is a LearnOpenGL chapter 7 baseline. It opens a resizable
OpenGL 3.3 window and draws two indexed, textured rectangles. The container
and transparent-face images are loaded from disk with `stb_image`, mixed in a
file-backed fragment shader, and transformed with GLM matrices. One rectangle
rotates while the other continuously scales. Press `Escape` to close the
application.

## Near-term milestone

Build a small gridless planning prototype that proves the core interaction
before expanding the economic simulation:

- Convert the mouse position into a point on the ground plane
- Draw and edit a simple road or planning boundary in world space
- Represent and select an irregular parcel independently of the test grid
- Apply a zoning category and one or two planning restrictions
- Visualise the parcel's current planning and development state
- Advance it through a minimal development sequence using placeholder geometry

This milestone should establish the parcel as the authoritative unit of play.
The existing tile grid may remain useful internally for terrain sampling or
other spatial queries, but it should not become the public building-placement
model.

## Technology

- C++20
- OpenGL 3.3
- GLFW 3.4 for windows, input, and the OpenGL context
- GLAD 2.0.8 for OpenGL loading
- GLM 1.0.3 for vectors, matrices, and camera transforms
- spdlog 1.17.0 for diagnostics
- stb_image for loading common image formats
- CMake with a Visual Studio 2022 preset

Wave function collapse and marching-cubes-style techniques are candidates for
later procedural generation work, once the planning and parcel model has been
validated.

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
project.

## Controls

- `Escape`: close the application

## Documentation

Generate the HTML API documentation after configuring the project:

```powershell
cmake --build build --target docs
```

Then open `build/docs/html/index.html`.

## Project layout

```text
assets/shaders/          Runtime GLSL vertex and fragment shaders
assets/textures/         LearnOpenGL sample textures
include/CityBuilder/     Engine-facing C++ interfaces
src/Rendering/           Shader loading, compilation, and uniforms
src/ThirdParty/          stb_image implementation translation unit
src/main.cpp             Chapter 7 application and render loop
vendor/glad/             Generated OpenGL loader
vendor/stb/              Single-header image loader
.github/workflows/       Continuous integration
```

## Learning source

The baseline follows Joey de Vries' LearnOpenGL chapters
[Hello Triangle](https://learnopengl.com/Getting-started/Hello-Triangle) and
[Shaders](https://learnopengl.com/Getting-started/Shaders), then continues
through [Textures](https://learnopengl.com/Getting-started/Textures) and
[Transformations](https://learnopengl.com/Getting-started/Transformations).
See `THIRD_PARTY_NOTICES.md` for attribution and licensing.

## License

Licensed under the [MIT License](LICENSE).

The LearnOpenGL-adapted sample code and assets are separately licensed under CC
BY-NC 4.0 as described in `THIRD_PARTY_NOTICES.md`.
