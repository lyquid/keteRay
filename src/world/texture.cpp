#include "texture.hpp"
#include <glm/trigonometric.hpp>

ktp::Color ktp::CheckerTexture::value(double u, double v, const Vector& p) const {
  const auto sines {glm::sin(10.0 * p.x) * glm::sin(10.0 * p.y) * glm::sin(10.0 * p.z)};
  // if (sines < 0)
  //   return m_odd->value(u, v, p);
  // else
  //   return m_even->value(u, v, p);
  return sines < 0.0 ? m_odd->value(u, v, p) : m_even->value(u, v, p);
}
