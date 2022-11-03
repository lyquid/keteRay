/**
 * @file sphere.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Sphere class.
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KETERAY_SRC_WORLD_SPHERE_HPP_
#define KETERAY_SRC_WORLD_SPHERE_HPP_

#include "hittable.hpp"
#include "../renderer/renderer_types.hpp"

namespace ktp {

class Sphere: public Hittable {
 public:

  Sphere() = default;
  Sphere(const Point& center, double radius, MaterialPtr material):
    m_center(center), m_material(material), m_radius(radius) {}

  static void getSphereUV(const Point& p, double& u, double& v);

  bool boundingBox(AABB& output_box) const override;
  auto center() const { return m_center; }
  bool hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const override;
  auto radius() const { return m_radius; }

 private:

  Point       m_center {};
  MaterialPtr m_material {nullptr};
  double      m_radius {};
};

} // namespace ktp

#endif
