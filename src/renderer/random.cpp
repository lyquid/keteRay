#include "random.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include <chrono>
#include <random>

ktp::Color ktp::rng::randomColor(double min, double max) {
  return Color(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

double ktp::rng::randomDouble(double min, double max) {
  static std::uniform_real_distribution<double> dist(min, max);
  static std::mt19937 generator (std::chrono::steady_clock::now().time_since_epoch().count());
  return dist(generator);
}

ktp::Vector ktp::rng::randomInHemisphere(const Vector& normal) {
  const Vector in_unit_sphere {randomInUnitSphere()};
  return glm::dot(in_unit_sphere, normal) > 0.0 ? in_unit_sphere : -in_unit_sphere;
}

ktp::Vector ktp::rng::randomInUnitDisk() {
  while (true) {
    const auto p {Vector(randomDouble(-1.0, 1.0), randomDouble(-1.0, 1.0), 0.0)};
    if (glm::length2(p) >= 1.0) continue;
    return p;
  }
}

ktp::Vector ktp::rng::randomInUnitSphere() {
  while (true) {
    const auto p {randomVector(-1.0, 1.0)};
    if (glm::length2(p) >= 1.0) continue;
    return p;
  }
}

ktp::Vector ktp::rng::randomUnitVector() {
  return glm::normalize(randomVector());
}

ktp::Vector ktp::rng::randomVector(double min, double max) {
  return Vector(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}
