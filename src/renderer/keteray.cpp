#include "camera.hpp"
#include "keteray.hpp"
#include "random.hpp"
#include "ray.hpp"
#include "../world/hittable.hpp"
#include "../world/material.hpp"
#include <glm/gtx/norm.hpp>

std::string ktp::createFileName(const RenderData& render_data, const ppm::PPMFileData& file_data) {
  return file_data.m_name + "_"
    + std::to_string(render_data.m_width)             + "x"
    + std::to_string(render_data.m_height)            + "_"
    + std::to_string(render_data.m_samples_per_pixel) + "_samples.ppm";
}

void ktp::keteRay(const RenderData& render_data, ppm::PPMFileData& file_data, int& j) {
  // config of file_data
  file_data.m_width  = render_data.m_width;
  file_data.m_height = render_data.m_height;
  file_data.m_pixels.clear();
  file_data.m_pixels.reserve(file_data.m_width * file_data.m_height);
  file_data.m_file_name = createFileName(render_data, file_data);
  // Recursion depth for rayColor
  constexpr auto max_depth {50};
  // here we go!
  for (j = render_data.m_height - 1; j >= 0; --j) {
    std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < render_data.m_width; ++i) {
      Color pixel_color {};
      if (render_data.m_samples_per_pixel <= 1) {
        // no multisampling
        const auto u {static_cast<double>(i) / (render_data.m_width  - 1)};
        const auto v {static_cast<double>(j) / (render_data.m_height - 1)};
        const Ray ray {render_data.m_camera->getRay(u, v)};
        pixel_color = rayColor(ray, render_data.m_scene.m_background, render_data.m_scene.m_world, max_depth);
      } else {
        // multisampling
        for (int s = 0; s < render_data.m_samples_per_pixel; ++s) {
          const auto u {(i + rng::randomDouble()) / (render_data.m_width  - 1)};
          const auto v {(j + rng::randomDouble()) / (render_data.m_height - 1)};
          const Ray ray {render_data.m_camera->getRay(u, v)};
          pixel_color += rayColor(ray, render_data.m_scene.m_background, render_data.m_scene.m_world, max_depth);
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
  const auto cos_theta {fmin(glm::dot(-uv, n), 1.0)};
  const Vector r_out_perp {etai_over_etat * (uv + cos_theta * n)};
  const Vector r_out_parallel {-glm::sqrt(glm::abs(1.0 - glm::length2(r_out_perp))) * n};
  return r_out_perp + r_out_parallel;
}
