#include "camera.hpp"
#include <glm/glm.hpp>

ktp::Camera::Camera(double vfov, double aspect_ratio): m_aspect_ratio(aspect_ratio) {
  const auto theta {glm::radians(vfov)};
  const auto h {glm::tan(theta / 2.0)};
  const auto viewport_height {2.0 * h};
  const auto viewport_width {m_aspect_ratio * viewport_height};

  constexpr auto focal_length {1.0};

  m_origin = Point(0.0, 0.0, 0.0);
  m_horizontal = Vector(viewport_width, 0.0, 0.0);
  m_vertical = Vector(0.0, viewport_height, 0.0);
  m_lower_left_corner = m_origin - m_horizontal / 2.0 - m_vertical / 2.0 - Vector(0.0, 0.0, focal_length);
}
