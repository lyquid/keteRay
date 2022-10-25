/**
 * @file ray.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief A ray class for ray tracing purposes.
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef RAY_HPP_
#define RAY_HPP_

#include <glm/geometric.hpp> // glm::normalize
#include "owert.hpp"

namespace ktp {

class Hittable;

class Ray {
 public:

  constexpr Ray() = default;
  constexpr Ray(const glm::vec3& origin, const glm::vec3& direction): m_direction(direction), m_origin(origin) {}

  constexpr Point at(double t) const { return m_origin + t * m_direction; }
  constexpr auto direction() const { return m_direction; }
  Vector normalizeDirection() const { return glm::normalize(m_direction); }
  constexpr auto origin() const { return m_origin; }
  Color rayColor(const Hittable& world) const ;

 private:

  Vector m_direction {};
  Point  m_origin {};
};

} // namespace ktp

#endif
