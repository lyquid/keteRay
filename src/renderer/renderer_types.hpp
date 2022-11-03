/**
 * @file renderer_types.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Types for the renderer.
 * @version 0.1
 * @date 2022-11-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KETERAY_SRC_RENDERER_RENDERER_TYPES_HPP_
#define KETERAY_SRC_RENDERER_RENDERER_TYPES_HPP_

#include <glm/vec3.hpp>
#include <limits>

namespace ktp {

using Color  = glm::dvec3;
using Point  = glm::dvec3;
using Vector = glm::dvec3;

struct CameraConfig;
struct RenderData;

class Camera;
class Hittable;
class Ray;

constexpr auto k_INFINITY {std::numeric_limits<double>::infinity()};

} // namespace ktp

#endif
