#include "texture.hpp"
#include <glm/gtc/noise.hpp>
#include <glm/trigonometric.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "../../lib/stb_image.h"
#include <algorithm> // std::clamp
#include <fstream>
#include <iostream>

ktp::ImageTexture::ImageTexture(const std::string& file_name) {
  auto components_per_pixel {k_BYTES_PER_PIXEL};
  m_data = stbi_load(
    file_name.c_str(), &m_width, &m_height, &components_per_pixel, components_per_pixel
  );
  if (!m_data) {
    std::cerr << "ERROR: Could not load texture image file '" << file_name << "'.\n";
    m_width = m_height = 0;
  }
  m_bytes_per_scanline = k_BYTES_PER_PIXEL * m_width;
}

ktp::Color ktp::ImageTexture::value(double u, double v, const Vector& p) const {
  // If we have no texture data, then return solid cyan as a debugging aid.
  if (!m_data) return Color(0.0, 1.0, 1.0);

  // Clamp input texture coordinates to [0,1] x [1,0]
  u = std::clamp(u, 0.0, 1.0);
  v = 1.0 - std::clamp(v, 0.0, 1.0);  // Flip V to image coordinates

  auto i {static_cast<int>(u * m_width)};
  auto j {static_cast<int>(v * m_height)};

  // Clamp integer mapping, since actual coordinates should be less than 1.0
  if (i >= m_width)  i = m_width - 1;
  if (j >= m_height) j = m_height - 1;

  constexpr auto k_COLOR_SCALE {1.0 / 255.0};
  const auto pixel {m_data + j * m_bytes_per_scanline + i * k_BYTES_PER_PIXEL};

  return Color(pixel[0] * k_COLOR_SCALE, pixel[1] * k_COLOR_SCALE, pixel[2] * k_COLOR_SCALE);
}

ktp::Color ktp::CheckerTexture::value(double u, double v, const Vector& p) const {
  const auto sines {glm::sin(10.0 * p.x) * glm::sin(10.0 * p.y) * glm::sin(10.0 * p.z)};
  return sines < 0.0 ? m_odd->value(u, v, p) : m_even->value(u, v, p);
}

ktp::Color ktp::NoiseTexture::value(double u, double v, const Vector& p) const {
  return {Color(1.0, 1.0, 1.0) * ((glm::perlin(p * m_scale) + 1.0) / 2.0 )};
}
