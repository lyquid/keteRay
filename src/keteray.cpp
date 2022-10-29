#include "camera.hpp"
#include "hittable.hpp"
#include "keteray.hpp"
#include "material.hpp"
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
  std::cout << "\rRendering finished.                                      \n";
}

bool ktp::nearZero(const Vector& v) {
  constexpr auto s {1e-8};
  return glm::abs(v.x) < s && glm::abs(v.y) < s && glm::abs(v.z) < s;
}

double ktp::randomDouble(double min, double max) {
  static std::uniform_real_distribution<double> dist(min, max);
  static std::mt19937 generator {};
  return dist(generator);
}

ktp::Vector ktp::randomInHemisphere(const Vector& normal) {
  const Vector in_unit_sphere {randomInUnitSphere()};
  return glm::dot(in_unit_sphere, normal) > 0.0 ? in_unit_sphere : -in_unit_sphere;
}

ktp::Vector ktp::randomInUnitDisk() {
  while (true) {
    const auto p {Vector(randomDouble(-1.0, 1.0), randomDouble(-1.0, 1.0), 0.0)};
    if (glm::length2(p) >= 1.0) continue;
    return p;
  }
}

ktp::Vector ktp::randomInUnitSphere() {
  while (true) {
    const auto p {randomVector(-1.0, 1.0)};
    if (glm::length2(p) >= 1.0) continue;
    return p;
  }
}

ktp::Vector ktp::randomUnitVector() {
  return glm::normalize(randomVector());
}

ktp::Vector ktp::randomVector(double min, double max) {
  return Vector(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

ktp::Color ktp::rayColor(const Ray& ray, const Hittable* world, int depth) {
  HitRecord record {};
  // exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0) return Color(0.0, 0.0, 0.0);

  if (world->hit(ray, 0.001, k_INFINITY, record)) {
    Ray scattered {};
    Color attenuation {};
    if (record.m_material->scatter(ray, record, attenuation, scattered)) {
      return attenuation * rayColor(scattered, world, depth - 1);
    }
    return Color(0.0, 0.0, 0.0);
  }

  const auto t {0.5 * (ray.normalizeDirection().y + 1.0)};
  return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.5, 0.7, 1.0);
}

ktp::Vector ktp::refract(const Vector& uv, const Vector& n, double etai_over_etat) {
  const auto cos_theta {fmin(glm::dot(-uv, n), 1.0)};
  const Vector r_out_perp {etai_over_etat * (uv + cos_theta * n)};
  const Vector r_out_parallel {-glm::sqrt(glm::abs(1.0 - glm::length2(r_out_perp))) * n};
  return r_out_perp + r_out_parallel;
}
