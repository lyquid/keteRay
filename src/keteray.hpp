/**
 * @file owert.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Utilities for the app.
 * @version 0.1
 * @date 2022-10-24
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KTP_OWERT_HPP_
#define KTP_OWERT_HPP_

#include "libppm.hpp"
#include <glm/vec3.hpp>
#include <limits>

namespace ktp {

using Color  = glm::dvec3;
using Point  = glm::dvec3;
using Vector = glm::dvec3;

class Camera;
class Ray;
class Hittable;

constexpr auto k_INFINITY {std::numeric_limits<double>::infinity()};

struct RenderData {
  Camera*   m_camera {nullptr};
  int       m_samples_per_pixel {};
  Hittable* m_world {nullptr};
};

inline ppm::Color colorToPPM(const Color& color) {
  return ppm::Color{color.r, color.g, color.b};
}

void keteRay(const RenderData& render_data, ppm::PPMFileData& file_data);

double randomDouble(double min = 0.0, double max = 1.0);

// Alternate diffuse.
Vector randomInHemisphere(const Vector& normal);

// Hack diffuse
Vector randomInUnitSphere();

// Lambertian diffuse.
Vector randomUnitVector();

Vector randomVector(double min = 0.0, double max = 1.0);

Color rayColor(const Ray& ray, const Hittable* world, int depth);

} // namespace ktp

#endif
