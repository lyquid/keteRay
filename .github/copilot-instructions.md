# keteRay — Copilot Instructions

> *"These are the ancient runes. Study them well, young Padawan."*

## Project Overview

**keteRay** is a physically-based CPU ray tracer written in **C++20**, inspired by
[Ray Tracing in One Weekend](https://raytracing.github.io/).
It renders 3D scenes with physically accurate light simulation (diffuse, metal, glass, emissive)
and exposes a live GUI preview via **SFML + Dear ImGui**.

---

## Directory Layout

```
src/
  gui/          # SFML window + ImGui integration; do NOT put rendering logic here
  renderer/     # Ray casting, camera model, BVH, random number utilities
  world/        # Scene objects (Hittable subclasses), materials, textures, scene loader
  config.cpp/hpp  # JSON config parsing with nlohmann_json
  libppm.hpp    # Self-contained PPM image writer (header-only)
  types.hpp     # All global type aliases and forward declarations — edit with care
  main.cpp      # Entry point only — keep thin
config/
  config.json   # Runtime config for camera, render settings, and scene selection
resources/      # Image files used as textures
```

---

## Language & Standard

- **C++20** — use modern features: structured bindings, `[[nodiscard]]`, `std::span`, concepts,
  `std::numbers`, `constexpr` where applicable, and range-based algorithms.
- **C++ Core Guidelines** are enforced via clang-tidy. Do **not** disable checks without
  a well-documented reason.
- No raw `new`/`delete` — use `std::make_shared` / `std::make_unique`.
- Prefer `const` by default; mark members `const` and functions `const` whenever possible.
- Prefer value semantics; use smart pointers (`std::shared_ptr`, `std::unique_ptr`) for
  ownership.

---

## Naming Conventions

| Thing | Convention | Example |
|---|---|---|
| Types / classes | `CamelCase` | `HittableList`, `Lambertian` |
| Functions / methods | `camelCase` | `getRay()`, `nearZero()` |
| Member variables | `m_snake_case` | `m_aspect_ratio`, `m_width` |
| Free constants | `k_UPPER_SNAKE` | `k_INFINITY`, `k_MAX_DEPTH` |
| Namespaces | `lowercase` | `ktp`, `ktp::scn`, `ktp::rng`, `ppm` |
| File names | `snake_case.hpp/.cpp` | `random.hpp`, `keteray.cpp` |

All source files use include guards in the style:
```cpp
#ifndef KETERAY_SRC_<SUBDIR>_<FILENAME>_HPP_
#define KETERAY_SRC_<SUBDIR>_<FILENAME>_HPP_
// ...
#endif
```

---

## Type Aliases (defined in `src/types.hpp`)

```cpp
using Color   = glm::dvec3;   // RGB colour, components in [0, 1]
using Point   = glm::dvec3;   // 3D world-space position
using Vector  = glm::dvec3;   // 3D direction vector
using HittablePtr = std::shared_ptr<Hittable>;
using MaterialPtr = std::shared_ptr<Material>;
using TexturePtr  = std::shared_ptr<Texture>;
```

Always use these aliases instead of raw GLM types to keep the code readable.

---

## Key Abstractions

### `Hittable` (world/hittable.hpp)
Abstract base for everything a ray can intersect. Implement `hit()` and `boundingBox()`.

### `Material` (world/material.hpp)
Abstract base for surface behaviour. Implement `scatter()` and optionally `emitted()`.

### `Texture` (world/texture.hpp)
Abstract base for surface colour lookup. Implement `value(u, v, point)`.

### `Camera` (renderer/camera.hpp)
Generates rays. Constructed from a `CameraConfig` struct. Call `getRay(s, t)` to sample.

### `Scene` (world/scene.hpp)
Holds a `HittableList` world, a background `Color`, and scene metadata.
Scenes are registered in `scn::loadScenes()` and stored in the global `scenes` map.

---

## Adding a New Scene

1. Add a function declaration in `src/world/scene.hpp` inside `namespace ktp::scn`.
2. Implement it in `src/world/scene.cpp` — return a `HittableList`.
3. Register it in `scn::loadScenes()` with a string key and a `Color` background.
4. Select it via `config.json` → `"render": { "scene": "your_key" }`.

---

## Adding a New Material

1. Inherit from `Material` in `src/world/material.hpp`.
2. Implement `bool scatter(...)`.
3. Optionally override `Color emitted(...)` for emissive materials.
4. Use `std::make_shared<YourMaterial>(...)` at the call site.

---

## Random Numbers

Use the `ktp::rng` namespace (`src/renderer/random.hpp`):
```cpp
rng::randomDouble();          // [0, 1)
rng::randomDouble(min, max);  // [min, max)
rng::randomInt(min, max);     // [min, max]
rng::randomUnitVector();      // unit sphere surface sample
rng::randomInUnitDisk();      // unit disk (for DOF)
```

Never use `std::rand()` — the RNG gods will be displeased.

---

## Math Utilities

All vector/matrix math is done with **GLM** (`glm::dvec3`). Key helpers in `renderer/keteray.hpp`:
- `nearZero(v)` — check if a vector is near zero (avoids degenerate scatter directions)
- `reflect(v, normal)` — specular reflection
- `refract(uv, n, etai_over_etat)` — Snell's law refraction
- `colorToPPM(color)` — convert `ktp::Color` to `ppm::Color`

---

## CI & Code Style

- The CI workflow (`.github/workflows/ci.yml`) builds the project and runs **clang-tidy**.
- clang-tidy configuration is in `.clang-tidy` at the repo root.
- To run clang-tidy locally (requires `compile_commands.json`):
  ```bash
  cmake -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ...
  clang-tidy src/**/*.cpp --config-file=.clang-tidy
  ```
- The project follows the `.editorconfig` settings (2-space indent, LF line endings).

---

## Do & Don't

| ✅ Do | ❌ Don't |
|---|---|
| Use `auto` for verbose type names | Suppress clang-tidy warnings without comment |
| Use `[[nodiscard]]` on functions returning values that must be checked | Use `using namespace std;` in headers |
| Mark virtual destructors as `= default` | Mix tabs and spaces |
| Use range-for over raw index loops where possible | Use `std::rand()` or global mutable state |
| Write self-documenting code; add Doxygen `@brief` to public APIs | Add unrelated includes |
| Use `constexpr` for compile-time constants | Cast away `const` |

---

*May your rays never miss and your BVH always balance.* ⚡
