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
#include <memory>
#include <string>

namespace ktp {

class Texture {
 public:
  virtual ~Texture() {}
  virtual Color value(double u, double v, const Point& p) const = 0;
};

class ImageTexture: public Texture {
 public:
  ImageTexture() = default;
  ImageTexture(const std::string& file_name);
  ~ImageTexture() { delete m_data; }
  Color value(double u, double v, const Vector& p) const override;
 private:
  static constexpr int k_BYTES_PER_PIXEL {3};
  unsigned char* m_data {nullptr};
  int m_width{}, m_height{};
  int m_bytes_per_scanline{};
};

class MarbleTexture: public Texture {
 public:
  MarbleTexture() = default;
  MarbleTexture(double scale, const Color& color = {1.0, 1.0, 1.0}):
    m_color(color),
    m_scale(scale) {}
  Color value(double u, double v, const Vector& p) const override;
 private:
  Color m_color {1.0, 1.0, 1.0};
  double m_scale {1};
};

class NoiseTexture: public Texture {
 public:
  NoiseTexture() = default;
  NoiseTexture(double scale, const Color& color = {1.0, 1.0, 1.0}):
    m_color(color),
    m_scale(scale) {}
  Color value(double u, double v, const Vector& p) const override;
 private:
  Color m_color {1.0, 1.0, 1.0};
  double m_scale {1};
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

class CheckerTexture: public Texture {
 public:
  CheckerTexture() = default;
  CheckerTexture(TexturePtr even, TexturePtr odd): m_even(even), m_odd(odd) {}
  CheckerTexture(const Color& c1, const Color& c2):
    m_even(std::make_shared<SolidColor>(c1)), m_odd(std::make_shared<SolidColor>(c2)) {}
  Color value(double u, double v, const Vector& p) const override;
 private:
  TexturePtr m_even {nullptr};
  TexturePtr m_odd {nullptr};
};

class TurbulenceTexture: public Texture {
 public:
  TurbulenceTexture() = default;
  TurbulenceTexture(double scale, const Color& color = {1.0, 1.0, 1.0}):
    m_color(color),
    m_scale(scale) {}
  static double turbulence(const Point& p, int depth = 7);
  Color value(double u, double v, const Vector& p) const override;
 private:
  Color m_color {1.0, 1.0, 1.0};
  double m_scale {1};
};

} // namespace ktp

#endif
