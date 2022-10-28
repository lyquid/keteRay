#include "camera.hpp"
#include <glm/glm.hpp>

ktp::Camera::Camera(Point look_from, Point look_at, Vector vup, double vfov, double aspect_ratio):
  m_aspect_ratio(aspect_ratio), m_origin(look_from) {

  const auto theta {glm::radians(vfov)};
  const auto h {glm::tan(theta / 2.0)};
  const auto viewport_height {2.0 * h};
  const auto viewport_width {m_aspect_ratio * viewport_height};

  const auto w {glm::normalize(look_from - look_at)};
  const auto u {glm::normalize(glm::cross(vup, w))};
  const auto v {glm::cross(w, u)};

  m_horizontal = viewport_width * u;
  m_vertical = viewport_height * v;
  m_lower_left_corner = m_origin - m_horizontal / 2.0 - m_vertical / 2.0 - w;
}
