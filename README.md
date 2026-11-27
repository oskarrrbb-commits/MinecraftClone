# MinecraftClone
[![CI](https://github.com/oskarrrbb-commits/MinecraftClone/actions/workflows/ci.yml/badge.svg)](https://github.com/oskarrrbb-commits/MinecraftClone/actions/workflows/ci.yml)
A small voxel engine inspired by Minecraft, written in C++ with OpenGL 3.3, as a learning project.

Right now it generates a 2×2 grid of 16×16×16 chunks (stone, dirt and grass layers), builds a mesh per chunk that skips hidden faces, and lets you fly around with a free camera.

**Tech:** C++, OpenGL 3.3 core, [SDL3](https://github.com/libsdl-org/SDL) (window/input), [GLAD](https://github.com/Dav1dde/glad) (GL loader), [GLM](https://github.com/g-truc/glm) (math). SDL3 and GLM are downloaded automatically by CMake.

## Building

Requirements: CMake 3.20+, a C++17 compiler, and git. It is set up for **MinGW-w64 / GCC** (e.g. MSYS2 UCRT64), because `CMakeLists.txt` uses GCC-style static link flags.

```sh
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
./build/MinecraftClone.exe
```

The first configure step takes a while, because it downloads and builds SDL3.

## Controls

| Key | Action |
|-----|--------|
| W / A / S / D | Move |
| Mouse | Look around |
| Alt+F4 | Quit (the mouse is captured) |

## Project layout

```
src/
  core/      SDL init, window, OpenGL context, main loop (Application)
  renderer/  Camera, Mesh (VAO/VBO/EBO wrapper)
  world/     Block types, Chunk (voxel data + meshing), ChunkManager
external/    GLAD
```
