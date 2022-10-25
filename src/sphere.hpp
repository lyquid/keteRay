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

#ifndef KTP_SPHERE_HPP_
#define KTP_SPHERE_HPP_

#include "hittable.hpp"
#include "owert.hpp"

namespace ktp {

class Sphere: public Hittable {
 public:

  Sphere() = default;
  Sphere(const Point& center, double radius): m_center(center), m_radius(radius) {}
  auto center() const { return m_center; }
  bool hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const override;
  auto radius() const { return m_radius; }

 private:

  Point  m_center {};
  double m_radius {};
};

} // namespace ktp

#endif
