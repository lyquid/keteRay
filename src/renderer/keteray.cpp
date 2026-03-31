#include "camera.hpp"
#include "keteray.hpp"
#include "random.hpp"
#include "ray.hpp"
#include "../world/hittable.hpp"
#include "../world/material.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include <glm/common.hpp>       // glm::min, glm::clamp, glm::sqrt
#include <SFML/Graphics/Color.hpp>
#include <algorithm> // std::replace
#include <atomic>
#include <cstdint>

std::string ktp::createFileName(const RenderData& render_data) {
  auto scene_name {render_data.m_scene.m_name};
  std::replace(scene_name.begin(), scene_name.end(), ' ', '_');
  return scene_name + "_"
    + std::to_string(render_data.m_width)             + "x"
    + std::to_string(render_data.m_height)            + "_"
    + std::to_string(render_data.m_samples_per_pixel) + "_samples.png";
}

void ktp::keteRay(const RenderData& render_data, sf::Image& image, std::atomic<int>& j) {
  constexpr auto k_MAX_DEPTH {50};
  constexpr auto k_COLOR_LEVELS {256};
  image.resize({static_cast<unsigned>(render_data.m_width), static_cast<unsigned>(render_data.m_height)});
  // here we go!
  for (j = render_data.m_height - 1; j >= 0; --j) {
    std::cout << "\rScanlines remaining: " << j.load() << ' ' << std::flush;
    for (int i = 0; i < render_data.m_width; ++i) {
      Color pixel_color {};
      if (render_data.m_samples_per_pixel <= 1) {
        // no multisampling
        const auto u {static_cast<double>(i) / (render_data.m_width  - 1)};
        const auto v {static_cast<double>(j.load()) / (render_data.m_height - 1)};
        const Ray ray {render_data.m_camera->getRay(u, v)};
        pixel_color += rayColor(ray, render_data.m_scene.m_background, render_data.m_scene.m_world, k_MAX_DEPTH);
      } else {
        // multisampling
        for (int s = 0; s < render_data.m_samples_per_pixel; ++s) {
          const auto u {(i + rng::randomDouble()) / (render_data.m_width  - 1)};
          const auto v {(j.load() + rng::randomDouble()) / (render_data.m_height - 1)};
          const Ray ray {render_data.m_camera->getRay(u, v)};
          pixel_color += rayColor(ray, render_data.m_scene.m_background, render_data.m_scene.m_world, k_MAX_DEPTH);
        }
        const auto scale {1.0 / render_data.m_samples_per_pixel};
        pixel_color *= scale;
      }
      // gamma correction
      pixel_color = glm::sqrt(pixel_color);
      // j=height-1 → image y=0 (top row); j=0 → image y=height-1 (bottom row)
      const auto pixel_y {static_cast<unsigned>(render_data.m_height - 1 - j.load())};
      image.setPixel(
        {static_cast<unsigned>(i), pixel_y},
        sf::Color(
          static_cast<std::uint8_t>(k_COLOR_LEVELS * glm::clamp(pixel_color.r, 0.0, 0.999)),
          static_cast<std::uint8_t>(k_COLOR_LEVELS * glm::clamp(pixel_color.g, 0.0, 0.999)),
          static_cast<std::uint8_t>(k_COLOR_LEVELS * glm::clamp(pixel_color.b, 0.0, 0.999)),
          255u
        )
      );
    }
  }
  std::cout << "\rRendering finished.                                      \n";
}

bool ktp::nearZero(const Vector& v) {
  constexpr auto s {1e-8};
  return glm::abs(v.x) < s && glm::abs(v.y) < s && glm::abs(v.z) < s;
}

ktp::Color ktp::rayColor(const Ray& ray, const Color& background, const Hittable& world, int depth) {
  HitRecord record {};
  // exceeded the ray bounce limit, no more light is gathered.
  if (depth <= 0) return Color(0.0, 0.0, 0.0);

  // if the ray hits nothing, return the background color.
  if (!world.hit(ray, 0.001, k_INFINITY, record)) return background;

  Ray scattered {};
  Color attenuation {};
  Color emitted {record.m_material->emitted(record.m_u, record.m_v, record.m_point)};

  if (!record.m_material->scatter(ray, record, attenuation, scattered)) return emitted;

  return emitted + attenuation * rayColor(scattered, background, world, depth - 1);
}

ktp::Vector ktp::refract(const Vector& uv, const Vector& n, double etai_over_etat) {
  const auto cos_theta {glm::min(glm::dot(-uv, n), 1.0)};
  const Vector r_out_perp {etai_over_etat * (uv + cos_theta * n)};
  const Vector r_out_parallel {-glm::sqrt(glm::abs(1.0 - glm::length2(r_out_perp))) * n};
  return r_out_perp + r_out_parallel;
}
