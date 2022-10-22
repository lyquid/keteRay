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

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

namespace ktp {

using Point  = glm::dvec3;
using Vector = glm::dvec3;;

class Ray {
 public:

  Ray() = default;
  Ray(const glm::vec3& origin, const glm::vec3& direction): m_direction(direction), m_origin(origin) {}

  Point at(double t) const { return m_origin + t * m_direction; }
  auto direction() const { return m_direction; }
  Vector normalizeDirection() const { return glm::normalize(m_direction); }
  auto origin() const { return m_origin; }

 private:

  Vector m_direction {};
  Point m_origin {};
};

} // namespace ktp

#endif
