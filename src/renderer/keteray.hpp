/**
 * @file keteray.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Utilities for the app.
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KETERAY_SRC_RENDERER_KETERAY_HPP_
#define KETERAY_SRC_RENDERER_KETERAY_HPP_

#include "../types.hpp"
#include "../world/scene.hpp"
#include <atomic>
#include <glm/geometric.hpp>
#include <string>
#include <vector>

namespace ktp {

struct ImageData {
  std::string        m_file_name {};
  int                m_height {};
  std::vector<Color> m_pixels {};
  int                m_width {};
};

struct RenderData {
  Camera* m_camera {nullptr};
  int     m_height {};
  int     m_samples_per_pixel {};
  int     m_width {};
  Scene   m_scene {};
};

std::string createFileName(const RenderData& render_data, const ImageData& image_data);

void keteRay(const RenderData& render_data, ImageData& image_data, std::atomic<int>& j);

/**
 * @brief Checks if a vector is near 0 in all dimensions.
 * @param v The vector to check.
 * @return True if the vector is very close to zero in all dimensions.
 * False otherwise
 */
bool nearZero(const Vector& v);

Color rayColor(const Ray& ray, const Color& background, const Hittable& world, int depth);

inline Vector reflect(const Vector& v, const Vector& normal) {
  return v - 2 * glm::dot(v, normal) * normal;
}

Vector refract(const Vector& uv, const Vector& n, double etai_over_etat);

} // namespace ktp

#endif
