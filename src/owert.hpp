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
#include <random>

namespace ktp {

using Color  = glm::dvec3;
using Point  = glm::dvec3;
using Vector = glm::dvec3;

constexpr auto k_INFINITY {std::numeric_limits<double>::infinity()};

inline ppm::Color colorToPPM(const Color& color) {
  return ppm::Color{color.r, color.g, color.b};
}

inline auto randomDouble() {
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  std::mt19937 generator {};
  return dist(generator);
}

} // namespace ktp

#endif
