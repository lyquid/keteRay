#include "hittable.hpp"
#include "ray.hpp"

ktp::Color ktp::Ray::rayColor(const Hittable& world) const {
  HitRecord record {};
  if (world.hit(*this, 0.0, k_INFINITY, record)) {
    return 0.5 * (record.m_normal + Color(1.0, 1.0, 1.0));
  }
  Vector unit_direction {normalizeDirection()};
  auto t {0.5 * (unit_direction.y + 1.0)};
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}
