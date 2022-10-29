#include "camera.hpp"
#include <glm/glm.hpp>

ktp::Camera::Camera(Point look_from, Point look_at, Vector vup, double focus_dist, double vfov, double aspect_ratio, double aperture):
  m_aspect_ratio(aspect_ratio), m_origin(look_from), m_lens_radius(aperture / 2.0) {

  const auto theta {glm::radians(vfov)};
  const auto h {glm::tan(theta / 2.0)};
  const auto viewport_height {2.0 * h};
  const auto viewport_width {m_aspect_ratio * viewport_height};

  m_w = glm::normalize(look_from - look_at);
  m_u = glm::normalize(glm::cross(vup, m_w));
  m_v = glm::cross(m_w, m_u);

  m_horizontal = focus_dist * viewport_width * m_u;
  m_vertical = focus_dist * viewport_height * m_v;
  m_lower_left_corner = m_origin - m_horizontal / 2.0 - m_vertical / 2.0 - focus_dist * m_w;
}
