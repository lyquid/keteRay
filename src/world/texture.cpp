#include "texture.hpp"
#include <glm/gtc/noise.hpp>
#include <glm/trigonometric.hpp>
#include <algorithm> // std::clamp
#include <iostream>

ktp::ImageTexture::ImageTexture(const std::string& file_name) {
  auto loaded {sf::Image::loadFromFile(file_name)};
  if (!loaded) {
    std::cerr << "ERROR: Could not load texture image file '" << file_name << "'.\n";
  } else {
    m_image = std::move(*loaded);
  }
}

ktp::Color ktp::ImageTexture::value(double u, double v, const Vector& p) const {
  // If we have no texture data, then return solid cyan as a debugging aid.
  if (m_image.getSize().x == 0 || m_image.getSize().y == 0) return Color(0.0, 1.0, 1.0);

  // Clamp input texture coordinates to [0,1] x [1,0]
  u = std::clamp(u, 0.0, 1.0);
  v = 1.0 - std::clamp(v, 0.0, 1.0);  // Flip V to image coordinates

  auto pixel_x {static_cast<unsigned int>(u * static_cast<double>(m_image.getSize().x))};
  auto pixel_y {static_cast<unsigned int>(v * static_cast<double>(m_image.getSize().y))};

  // Clamp integer mapping, since actual coordinates should be less than 1.0
  if (pixel_x >= m_image.getSize().x) pixel_x = m_image.getSize().x - 1u;
  if (pixel_y >= m_image.getSize().y) pixel_y = m_image.getSize().y - 1u;

  constexpr auto k_COLOR_SCALE {1.0 / 255.0};
  const auto pixel {m_image.getPixel({pixel_x, pixel_y})};

  return Color(pixel.r * k_COLOR_SCALE, pixel.g * k_COLOR_SCALE, pixel.b * k_COLOR_SCALE);
}

ktp::Color ktp::CheckerTexture::value(double u, double v, const Vector& p) const {
  const auto sines {glm::sin(10.0 * p.x) * glm::sin(10.0 * p.y) * glm::sin(10.0 * p.z)};
  return sines < 0.0 ? m_odd->value(u, v, p) : m_even->value(u, v, p);
}

ktp::Color ktp::MarbleTexture::value(double u, double v, const Vector& p) const {
  return m_color * 0.5 * (1.0 + glm::sin(m_scale * p.z + 10.0 * TurbulenceTexture::turbulence(p)));
}

ktp::Color ktp::NoiseTexture::value(double u, double v, const Vector& p) const {
  return m_color * ((glm::perlin(p * m_scale) + 1.0) / 2.0 );
}

double ktp::TurbulenceTexture::turbulence(const Point& p, int depth) {
  auto accum {0.0};
  auto temp_p {p};
  auto weight {1.0};

  for (int i = 0; i < depth; ++i) {
    accum += weight * glm::perlin(temp_p);
    weight *= 0.5;
    temp_p *= 2;
  }
  return glm::abs(accum);
}

ktp::Color ktp::TurbulenceTexture::value(double u, double v, const Vector& p) const {
  return m_color * turbulence(m_scale * p);
}
