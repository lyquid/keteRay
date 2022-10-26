#include "camera.hpp"
#include "hittable.hpp"
#include "keteray.hpp"
#include "ray.hpp"
#include <chrono>
#include <random>

void ktp::keteRay(const RenderData& render_data, ppm::PPMFileData& file_data) {
  // Recursion depth for rayColor
  constexpr auto max_depth {50};
  for (int j = file_data.m_height - 1; j >= 0; --j) {
    std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < file_data.m_width; ++i) {
      Color pixel_color {};
      if (render_data.m_samples_per_pixel <= 1) {
        // no multisampling
        const auto u {static_cast<double>(i) / (file_data.m_width  - 1)};
        const auto v {static_cast<double>(j) / (file_data.m_height - 1)};
        const Ray ray {render_data.m_camera->getRay(u, v)};
        pixel_color = rayColor(ray, render_data.m_world, max_depth);
      } else {
        // multisampling
        for (int s = 0; s < render_data.m_samples_per_pixel; ++s) {
          const auto u {(i + randomDouble()) / (file_data.m_width  - 1)};
          const auto v {(j + randomDouble()) / (file_data.m_height - 1)};
          const Ray ray {render_data.m_camera->getRay(u, v)};
          pixel_color += rayColor(ray, render_data.m_world, max_depth);
        }
        const auto scale {1.0 / render_data.m_samples_per_pixel};
        pixel_color *= scale;
      }
      // gamma correction
      pixel_color = glm::sqrt(pixel_color);
      // final pixel color to the data
      file_data.m_pixels.push_back(colorToPPM(pixel_color));
    }
  }
}

double ktp::randomDouble(double min, double max) {
  static std::uniform_real_distribution<double> dist(min, max);
  static std::mt19937 generator {};
  return dist(generator);
}

ktp::Vector ktp::randomInHemisphere(const Vector& normal) {
  Vector in_unit_sphere {randomInUnitSphere()};
  return glm::dot(in_unit_sphere, normal) > 0.0 ? in_unit_sphere : -in_unit_sphere;
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

ktp::Color ktp::rayColor(const Ray& ray, const Hittable* world, int depth) {
  HitRecord record {};
  // exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0) return Color(0.0, 0.0, 0.0);

  if (world->hit(ray, 0.001, k_INFINITY, record)) {
    // hack diffuse
    // Point target {record.m_point + record.m_normal + randomInUnitSphere()};
    // Lambertian diffuse
    Point target {record.m_point + record.m_normal + randomUnitVector()};
    // alternate diffuse
    // Point target {record.m_point + randomInHemisphere(record.m_normal)};
    return 0.5 * rayColor(Ray(record.m_point, target - record.m_point), world, depth - 1);
  }

  Vector unit_direction {ray.normalizeDirection()};
  auto t {0.5 * (unit_direction.y + 1.0)};
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}
