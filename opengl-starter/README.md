# OpenGL Starter (C++17)

Minimal C++ OpenGL starter using CMake, GLFW, GLAD and GLM. It renders a spinning 3D cube.

Prerequisites
- `cmake` (>= 3.14)
- A C++17 toolchain (g++, clang++)
- (Optional) build-essential packages. On Debian/Ubuntu, install:

```bash
sudo apt update
sudo apt install build-essential cmake git libx11-dev libxrandr-dev libxi-dev libxcursor-dev libgl1-mesa-dev libglu1-mesa-dev
```

Build & Run

```bash
mkdir -p build
cmake -S . -B build
cmake --build build -j
./build/opengl-starter
```

Notes
- The project fetches GLFW, GLAD and GLM at configure time using CMake's FetchContent.
- If the build fails due to missing system packages, install the development packages listed above.
