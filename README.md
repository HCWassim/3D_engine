# 3D Engine in C

A lightweight software 3D engine written in C. Rendering is done on the CPU and displayed through [SDL2](https://www.libsdl.org/), so no OpenGL or Vulkan is required.

The project is modular: projection, camera, matrices, objects and display code live in separate files under `src/`.

## Features

- **Real-time 3D rendering**: perspective projection of 3D objects onto the 2D screen, computed by the engine itself.
- **Camera control**: move and rotate the camera with the keyboard and the mouse.
- **Flat shading**: each face is filled with a colour based on a directional light.
- **Face culling**: faces that point away from the camera are not drawn.
- **Matrix and vector utilities**: rotations, translations and projections in `matrix.c` and `projection.c`.

Work in progress: Perlin noise terrain generation (`map.c`) is implemented but not yet displayed in the scene.

## Project structure

```
3D_engine/
├── Makefile      build script
├── src/          source code (.c and .h files)
├── include/      SDL2 headers (see installation below)
└── lib/          SDL2 libraries (Windows only)
```

## Prerequisites

- A C compiler (GCC or MinGW on Windows)
- SDL2 development libraries (version 2.x)
- `make`

## Installation

### Linux (Debian / Ubuntu)

1. Install the required packages:

   ```bash
   sudo apt update
   sudo apt install build-essential libsdl2-dev
   ```

2. Clone the repository:

   ```bash
   git clone https://github.com/HCWassim/3D_engine.git
   cd 3D_engine
   ```

3. Create a link to the SDL2 headers in the project root. The source files include `"../include/SDL.h"`, so this link is required:

   ```bash
   ln -sfn /usr/include/SDL2 include
   ```

### Windows (MinGW)

1. Install [MinGW-w64](https://www.mingw-w64.org/) (or MSYS2) and download the **SDL2 development libraries for MinGW** from the [SDL releases page](https://github.com/libsdl-org/SDL/releases).

2. Clone the repository:

   ```bash
   git clone https://github.com/HCWassim/3D_engine.git
   cd 3D_engine
   ```

3. In the project root, create two folders:
   - `include/` containing the SDL2 headers (`SDL.h` and the other files from the SDL2 `include` folder);
   - `lib/` containing the SDL2 libraries for MinGW (`libSDL2.dll.a`, `libSDL2main.a`, etc.).

   The `SDL2.dll` file must be in the same folder as the compiled program, or in a folder listed in your `PATH`.

## Building

From the project root (the folder containing `Makefile`):

| Platform | Command |
|----------|---------|
| Linux | `make` |
| Windows (MinGW) | `mingw32-make` |

The executable is created in the project root: `prgm` on Linux, `prgm.exe` on Windows.

Other targets:

| Command | Description |
|---------|-------------|
| `make run` | Build and run the engine |
| `make debug` | Build with debug symbols (`-g -O0`) |
| `make clean` | Remove object files and the executable |
| `make rebuild` | Clean, then build again |

## Running

```bash
./prgm          # Linux
prgm.exe        # Windows
```

## Controls

| Input | Action |
|-------|--------|
| Arrow keys | Move the camera left, right, up and down |
| `A` / `R` | Move the camera forward / backward |
| Mouse movement | Rotate the camera |
| Window close | Quit |

## Contributing

Contributions are welcome. Please open an issue to discuss a change, then submit a pull request with a clear description of what you changed and why.

## Issues and support

If you encounter a problem or have a question, please [open an issue](https://github.com/HCWassim/3D_engine/issues).

## License

This project is licensed under the [MIT License](./LICENSE). You are free to use and modify the code, provided you credit the original authors.
