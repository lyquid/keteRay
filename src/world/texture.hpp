/**
 * @file texture.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Texture class.
 * @version 0.1
 * @date 2022-11-03
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KETERAY_SRC_WORLD_TEXTURE_HPP_
#define KETERAY_SRC_WORLD_TEXTURE_HPP_

#include "../types.hpp"

namespace ktp {

class Texture {
 public:
  virtual Color value(double u, double v, const Point& p) const = 0;
};

class SolidColor: public Texture {
 public:
  SolidColor() = default;
  SolidColor(const Color& color): m_color(color) {}
  SolidColor(double r, double g, double b): m_color(Color(r, g, b)) {}
  Color value(double u, double v, const Vector& p) const override {
    return m_color;
  }
 private:
  Color m_color {};
};

} // namespace ktp

#endif
