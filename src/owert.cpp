#include "hittable.hpp"
#include "owert.hpp"
#include "ray.hpp"
#include <glm/gtx/norm.hpp>
#include <chrono>
#include <random>

double ktp::randomDouble(double min, double max) {
  static std::uniform_real_distribution<double> dist(min, max);
  static std::mt19937 generator {};
  return dist(generator);
}

ktp::Vector ktp::randomInUnitSphere() {
  while (true) {
    const auto p {randomVector(-1.0, 1.0)};
    if (glm::length2(p) >= 1.0) continue;
    return p;
  }
}

ktp::Vector ktp::randomVector(double min, double max) {
  return Vector(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

ktp::Color ktp::rayColor(const ktp::Ray& ray, const ktp::Hittable& world, int depth) {
  HitRecord record {};
  // exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0) return Color(0.0, 0.0, 0.0);

  if (world.hit(ray, 0.0, k_INFINITY, record)) {
    Point target {record.m_point + record.m_normal + randomInUnitSphere()};
    return 0.5 * rayColor(Ray(record.m_point, target - record.m_point), world, depth - 1);
  }

  Vector unit_direction {ray.normalizeDirection()};
  auto t {0.5 * (unit_direction.y + 1.0)};
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}
