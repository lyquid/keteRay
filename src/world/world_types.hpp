/**
 * @file world_types.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Types for the world.
 * @version 0.1
 * @date 2022-11-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KETERAY_SRC_WORLD_WORLD_TYPES_HPP_
#define KETERAY_SRC_WORLD_WORLD_TYPES_HPP_

#include <memory>

namespace ktp {

struct HitRecord;

class AABB;
class BVHnode;
class Dielectric;
class Hittable;
class HittableList;
class Lambertian;
class Material;
class Metal;
class Sphere;
class Texture;
class SolidColor;

using HittablePtr = std::shared_ptr<Hittable>;
using MaterialPtr = std::shared_ptr<Material>;
using TexturePtr  = std::shared_ptr<Texture>;

} // namespace ktp

#endif
