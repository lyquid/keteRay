#include "rectangle.hpp"
#include "../renderer/ray.hpp"

bool ktp::Rectangle::boundingBox(AABB& output_box) const {
  // The bounding box must have non-zero width in each dimension, so pad the Z
  // dimension a small amount.
  output_box = AABB(Point(m_x0, m_y0, m_k - 0.0001), Point(m_x1, m_y1, m_k + 0.0001));
  return true;
}

bool ktp::Rectangle::hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const {
  const auto t {(m_k - ray.origin().z) / ray.direction().z};
  if (t < t_min || t > t_max) return false;

  const auto x {ray.origin().x + t * ray.direction().x};
  const auto y {ray.origin().y + t * ray.direction().y};
  if (x < m_x0 || x > m_x1 || y < m_y0 || y > m_y1) return false;

  record.m_u = (x - m_x0) / (m_x1 - m_x0);
  record.m_v = (y - m_y0) / (m_y1 - m_y0);
  record.m_t = t;
  const auto outward_normal {Vector(0.0, 0.0, 1.0)};
  record.setFaceNormal(ray, outward_normal);
  record.m_material = m_material;
  record.m_point = ray.at(t);
  return true;
}
