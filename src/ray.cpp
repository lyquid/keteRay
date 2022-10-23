#include "ray.hpp"

bool hitSphere(const ktp::Point& center, double radius, const ktp::Ray& ray) {
  const ktp::Vector oc {ray.origin() - center};
  const auto a {glm::dot(ray.direction(), ray.direction())};
  const auto b {2.0 * glm::dot(oc, ray.direction())};
  const auto c {glm::dot(oc, oc) - radius * radius};
  const auto discriminant {b * b - 4.0 * a * c};
  return discriminant > 0.0;
}

ktp::Color ktp::Ray::rayColor() const {
  if (hitSphere(ktp::Point(0.0, 0.0, -1.0), 0.5, *this))
    return ktp::Color(1.0, 0.0, 0.0);
  const auto t {0.5 * (normalizeDirection().y + 1.0)};
  // interpolate
  return (1.0 - t) * ktp::Color(1.0, 1.0, 1.0) + t * ktp::Color(0.5, 0.7, 1.0);
}
