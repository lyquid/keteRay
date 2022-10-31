#include "camera.hpp"
#include <glm/glm.hpp>

ktp::Camera::Camera(Point look_from, Point look_at, Vector vup, double focus_dist, double vfov, double aspect_ratio, double aperture) {
  reset({
    aperture,
    aspect_ratio,
    focus_dist,
    look_at,
    look_from,
    vup,
    vfov
  });
}

void ktp::Camera::reset(const CameraConfig& config) {
  m_lens_radius = config.m_aperture / 2.0;
  m_aspect_ratio = config.m_aspect_ratio;

  const auto theta {glm::radians(config.m_vfov)};
  const auto h {glm::tan(theta / 2.0)};
  const auto viewport_height {2.0 * h};
  const auto viewport_width {m_aspect_ratio * viewport_height};

  m_w = glm::normalize(config.m_look_from - config.m_look_at);
  m_u = glm::normalize(glm::cross(config.m_vertical, m_w));
  m_v = glm::cross(m_w, m_u);

  m_origin = config.m_look_from;
  m_horizontal = config.m_focus_dist * viewport_width * m_u;
  m_vertical = config.m_focus_dist * viewport_height * m_v;
  m_lower_left_corner = m_origin - m_horizontal / 2.0 - m_vertical / 2.0 - config.m_focus_dist * m_w;
}
