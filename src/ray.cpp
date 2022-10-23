#include "ray.hpp"

auto hitSphere(const ktp::Point& center, double radius, const ktp::Ray& ray) {
  const ktp::Vector oc {ray.origin() - center};
  const auto a {glm::length2(ray.direction())};
  const auto half_b {glm::dot(oc, ray.direction())};
  const auto c {glm::length2(oc) - radius * radius};
  const auto discriminant {half_b * half_b - a * c};

  if (discriminant < 0.0) {
    return -1.0;
  } else {
    return (-half_b - glm::sqrt(discriminant)) / a;
  }
}

ktp::Color ktp::Ray::rayColor() const {
  auto t {hitSphere(ktp::Point(0.0, 0.0, -1.0), 0.5, *this)};
  if (t > 0.0) {
    ktp::Vector N {glm::normalize(ktp::Vector(at(t) - ktp::Vector(0.0, 0.0, -1.0)))};
    return 0.5 * ktp::Color(N.x + 1.0, N.y + 1.0, N.z + 1.0);
  }
  t = 0.5 * (normalizeDirection().y + 1.0);
  // interpolate
  return (1.0 - t) * ktp::Color(1.0, 1.0, 1.0) + t * ktp::Color(0.5, 0.7, 1.0);
}
