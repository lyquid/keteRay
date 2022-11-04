/**
 * @file types.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Types for the app.
 * @version 0.1
 * @date 2022-11-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KETERAY_SRC_TYPES_HPP_
#define KETERAY_SRC_TYPES_HPP_

#include <glm/vec3.hpp>
#include <limits>
#include <memory>
#include <string>

namespace ktp {

struct CameraConfig;
struct FileConfig;
struct HitRecord;
struct RenderConfig;
struct RenderData;
struct Scene;

class AABB;
class BVHnode;
class Camera;
class CheckerTexture;
class Dielectric;
class Hittable;
class HittableList;
class Lambertian;
class Material;
class Metal;
class Ray;
class SolidColor;
class Sphere;
class Texture;

using Color  = glm::dvec3;
using Point  = glm::dvec3;
using Vector = glm::dvec3;

using HittablePtr = std::shared_ptr<Hittable>;
using MaterialPtr = std::shared_ptr<Material>;
using TexturePtr  = std::shared_ptr<Texture>;

constexpr auto k_INFINITY {std::numeric_limits<double>::infinity()};
const std::string k_DEFAULT_SCENE {"cover"};
}

#endif
