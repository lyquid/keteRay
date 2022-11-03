/**
 * @file random.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Random number generation utilities.
 * @version 0.1
 * @date 2022-11-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KETERAY_SRC_RENDERER_RANDOM_HPP_
#define KETERAY_SRC_RENDERER_RANDOM_HPP_

#include "../types.hpp"

namespace ktp { namespace rng {

Color randomColor(double min = 0.0, double max = 1.0);

double randomDouble(double min = 0.0, double max = 1.0);

// Alternate diffuse.
Vector randomInHemisphere(const Vector& normal);

Vector randomInUnitDisk();

inline int randomInt(int min, int max) {
  return static_cast<int>(randomDouble(min, max + 1));
}

// Hack diffuse
Vector randomInUnitSphere();

// Lambertian diffuse.
Vector randomUnitVector();

Vector randomVector(double min = 0.0, double max = 1.0);

} } // namespace rng / ktp

#endif
