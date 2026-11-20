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
├── include/      SDL2 headers (included in the repository)
└── lib/          SDL2 libraries (Windows only, not in the repository)
```

## Prerequisites

- A C compiler (GCC, on Linux or through MSYS2 on Windows)
- SDL2 libraries, version 2.x
- `make` (`mingw32-make` on Windows)

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

The SDL2 headers are already in `include/`. The `libsdl2-dev` package provides the libraries used at link time.

### Windows (MSYS2 / UCRT64)

1. **Install MSYS2** from [msys2.org](https://www.msys2.org/), keeping the default location `C:\msys64`.

2. **Open "MSYS2 UCRT64"** from the Start menu and update the system:

   ```bash
   pacman -Syu
   ```

   If MSYS2 asks you to close the terminal, close it, reopen **MSYS2 UCRT64** and run `pacman -Syu` again until there is nothing left to update.

3. **Install the compiler, make, SDL2 and git**:

   ```bash
   pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make mingw-w64-ucrt-x86_64-SDL2 git
   ```

   Answer `Y` if asked to confirm.

4. **Add the tools to the Windows PATH.** In **PowerShell**, run once:

   ```powershell
   [Environment]::SetEnvironmentVariable("Path", $env:Path + ";C:\msys64\ucrt64\bin", "User")
   ```

   Close all terminals and open a new PowerShell window. Check that the tools are found:

   ```powershell
   gcc --version
   mingw32-make --version
   ```

5. **Clone the repository** (in PowerShell, from the folder of your choice):

   ```powershell
   git clone https://github.com/HCWassim/3D_engine.git
   cd 3D_engine
   ```

   Without Git, download the ZIP from GitHub (**Code > Download ZIP**), extract it and open the extracted folder. The SDL2 headers in `include/` come with the repository.

6. **Add the SDL2 libraries and DLL.** These files are not in the repository, so copy them from MSYS2:

   ```powershell
   New-Item -ItemType Directory -Force lib

   # Libraries used at link time
   Copy-Item C:\msys64\ucrt64\lib\libSDL2.dll.a lib\
   Copy-Item C:\msys64\ucrt64\lib\libSDL2main.a lib\

   # DLL needed at run time, placed next to the executable
   Copy-Item C:\msys64\ucrt64\bin\SDL2.dll .
   ```

   At the end, the project root must contain: `Makefile`, `src\`, `include\`, `lib\` and `SDL2.dll`.

7. **Build and run**, from the project root in PowerShell:

   ```powershell
   mingw32-make
   .\prgm.exe
   ```

   Use `mingw32-make` on Windows, not `make`. The executable is created as `prgm.exe` in the project root.

## Building

From the project root (the folder containing `Makefile`):

| Platform | Command |
|----------|---------|
| Linux | `make` |
| Windows (MSYS2) | `mingw32-make` |

Other targets:

| Command | Description |
|---------|-------------|
| `make run` | Build and run the engine |
| `make debug` | Build with debug symbols (`-g -O0`) |
| `make clean` | Remove object files and the executable |
| `make rebuild` | Clean, then build again |

On Windows, replace `make` with `mingw32-make` in these commands.

## Running

```bash
./prgm          # Linux
.\prgm.exe      # Windows (PowerShell)
```

## Troubleshooting (Windows)

| Error | Cause | Solution |
|-------|-------|----------|
| `mingw32-make` is not recognised | The PATH was not updated | Re-run step 4, then open a new terminal |
| `../include/SDL.h: No such file or directory` | The repository was not cloned completely | Check that `include\SDL.h` exists, or run `git pull` |
| `cannot find -lSDL2` or `-lSDL2main` | Library files missing from `lib` | Re-run step 6 so that `lib\` contains `libSDL2.dll.a` and `libSDL2main.a` |
| The program closes immediately, with a message about `SDL2.dll` | DLL not next to the executable | Copy `SDL2.dll` into the project root (step 6) |
| `ERREUR: echec initialisation de renderer` | Missing or outdated graphics driver | Update the graphics card driver |

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
