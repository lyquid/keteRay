# ✨ keteRay

<div align="center">

[![CI](https://github.com/lyquid/keteRay/actions/workflows/ci.yml/badge.svg)](https://github.com/lyquid/keteRay/actions/workflows/ci.yml)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg?logo=cplusplus)](https://en.cppreference.com/w/cpp/20)
[![CMake](https://img.shields.io/badge/CMake-3.12+-green.svg?logo=cmake)](https://cmake.org/)
[![License: MIT](https://img.shields.io/badge/license-MIT-yellow.svg)](LICENSE)
[![vcpkg](https://img.shields.io/badge/deps-vcpkg-blue.svg)](https://vcpkg.io/)

*A physically-based ray tracer forged in the fires of "Ray Tracing in One Weekend", wielded by ketepincho.*

> "It's a trap!" — Admiral Ackbar, on aliasing without multisampling

</div>

---

## 🔭 What Is This?

**keteRay** is a physically-based CPU ray tracer built upon the legendary
[_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
series by Peter Shirley (a.k.a. the Dumbledore of ray tracing).

It renders scenes with:

- 🌑 **Lambertian (diffuse) materials** — matte surfaces that would make Bob Ross weep tears of joy
- 🪞 **Metallic materials** with configurable fuzz — shine on, you crazy diamond
- 💎 **Dielectric (glass) materials** — refract ALL the rays!
- 💡 **Emissive / diffuse-light materials** — let there be light (and global illumination)
- 🌍 **Image-based textures** (including Earth, because who doesn't want a globe-sphere?)
- 🎲 **Procedural textures** — Perlin noise, marble, turbulence, checker — like a wizard's wardrobe
- 📦 **Bounding Volume Hierarchy (BVH)** — because `O(n)` intersection tests are so 1984
- 📷 **Configurable camera** with depth of field and arbitrary positioning
- 🖼️ **Live GUI** powered by **SFML + Dear ImGui** — watch pixels materialize in real time
- 💾 **PPM image export** — timeless and dependency-free, like a good pair of jorts

---

## 🗺️ Project Structure

```
keteRay/
├── config/           # config.json — tweak scene, camera & render settings
├── resources/        # Image assets (textures, etc.)
├── src/
│   ├── gui/          # SFML + ImGui live preview window
│   ├── renderer/     # Camera, ray marching logic, BVH, random utilities
│   ├── world/        # Hittables, materials, textures, scenes
│   ├── config.cpp/hpp# Config file parsing (nlohmann_json)
│   ├── libppm.hpp    # PPM image writer — one header to rule them all
│   ├── types.hpp     # Global type aliases and forward declarations
│   └── main.cpp      # The One Entry Point
├── CMakeLists.txt    # CMake build system (C++20)
└── vcpkg.json        # vcpkg manifest — dependency grimoire
```

---

## ⚗️ Dependencies

| Library | Purpose | The Nerdy Way to Say It |
|---|---|---|
| [GLM](https://github.com/g-truc/glm) | Math (vectors, matrices) | Linear algebra from the future |
| [SFML](https://www.sfml-dev.org/) | Window & rendering | The friendly face behind the pixels |
| [Dear ImGui](https://github.com/ocornut/imgui) | GUI widgets | Immediate-mode UI sorcery |
| [ImGui-SFML](https://github.com/eliasdaler/imgui-sfml) | ImGui ↔ SFML bridge | Making two cool things even cooler together |
| [nlohmann/json](https://github.com/nlohmann/json) | JSON config parsing | JSON: it's just objects all the way down |
| [stb](https://github.com/nothings/stb) | Image loading | Single-header libraries = true minimalism |

---

## 🧙 Building the Spell (Installation)

### Prerequisites

- **CMake ≥ 3.12**
- **C++20-capable compiler** (GCC ≥ 10, Clang ≥ 11, or MSVC 2019+)
- **[vcpkg](https://vcpkg.io/)** — the package manager Aragorn would use
- A display / OpenGL context (for the GUI window)

### 1. Install vcpkg (if you haven't already)

```bash
git clone https://github.com/microsoft/vcpkg.git ~/vcpkg
~/vcpkg/bootstrap-vcpkg.sh   # or bootstrap-vcpkg.bat on Windows
export VCPKG_ROOT=~/vcpkg    # add to your shell profile for persistence
```

### 2. Configure & Build

```bash
git clone https://github.com/lyquid/keteRay.git
cd keteRay

cmake -B build \
  -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" \
  -DCMAKE_BUILD_TYPE=Release

cmake --build build --config Release --parallel
```

> 💡 On Windows, drop the `export` line and use the Developer Command Prompt like the chosen one you are.

---

## 🚀 Usage

```bash
# Run with default config (binary is built into build/src/)
cd build/src && ./keteray

# Override samples per pixel (more = prettier, slower)
cd build/src && ./keteray samples=50

# Override render width
cd build/src && ./keteray width=1920

# Combine spells
cd build/src && ./keteray samples=100 width=1280
```

A live preview window will open — watch as the image materialises scanline by scanline, like a Polaroid from another dimension. When rendering is done, click **Save PPM** to write the image to disk.

### Tweaking the Config

Edit `config/config.json` to change the scene, camera, and render settings:

```json
{
  "camera": {
    "aperture": 0.0,
    "aspectRatio": {"w": 16.0, "h": 9.0},
    "focusDist": 10.0,
    "lookFrom": [13.0, 2.0, 3.0],
    "lookAt":   [0.0, 0.0, 0.0],
    "vertical": [0.0, 1.0, 0.0],
    "vFov": 20
  },
  "render": {
    "backgroundColor": [0.7, 0.8, 1.0],
    "samples": 10,
    "scene": "earth",
    "width": 400
  }
}
```

**Available scenes:** `cover`, `earth`, `checkered`, `marble`, `perlin`, `turbulence`, `simpleLight`, `threeSpheres`

---

## 🤝 Contributing

1. Fork the repository (and name your fork something cool)
2. Create a feature branch (`git checkout -b feat/add-pathtracing-unicorns`)
3. Write code that passes CI — the linter is watching 👁️
4. Submit a PR with a description Gandalf would approve of

> *"Commit early, commit often, and never feed Gremlins after midnight."*

---

## 👾 Credits & Acknowledgements

- 📖 **Peter Shirley** — [_Ray Tracing in One Weekend_](https://raytracing.github.io/) — the One Book to rule them all
- 🧑‍💻 **ketepincho** — the author and chief ray-casting wizard of this repo
- 🤖 **GitHub Copilot** — the trusty sidekick who helped write this very README
- 🧙 **Bjarne Stroustrup** — for giving us C++ (and the Core Guidelines to survive it)
- ☕ **Coffee** — the true rendering engine

---

## 📜 License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for details.

---

<div align="center">

*"There is no spoon... only rays."* 🥄

</div>

