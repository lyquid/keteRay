#include "texture.hpp"
#include <glm/gtc/noise.hpp>
#include <glm/trigonometric.hpp>
#include <fstream>

ktp::Color ktp::CheckerTexture::value(double u, double v, const Vector& p) const {
  const auto sines {glm::sin(10.0 * p.x) * glm::sin(10.0 * p.y) * glm::sin(10.0 * p.z)};
  return sines < 0.0 ? m_odd->value(u, v, p) : m_even->value(u, v, p);
}


ktp::Color ktp::NoiseTexture::value(double u, double v, const Vector& p) const {
  return {Color(1.0, 1.0, 1.0) * ((glm::perlin(p * m_scale) + 1.0) / 2.0 )};
}
