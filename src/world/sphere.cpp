#include "../renderer/keteray.hpp"
#include "../renderer/ray.hpp"
#include "sphere.hpp"
#include <glm/gtx/norm.hpp> // glm::dot, glm::length2

 bool ktp::Sphere::boundingBox(AABB& output_box) const {
  output_box = AABB(
    m_center - Vector(m_radius, m_radius, m_radius),
    m_center + Vector(m_radius, m_radius, m_radius)
  );
  return true;
 }

bool ktp::Sphere::hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const {
  const Vector oc {ray.origin() - m_center};
  const auto a {glm::length2(ray.direction())};
  const auto half_b {glm::dot(oc, ray.direction())};
  const auto c {glm::length2(oc) - m_radius * m_radius};
  const auto discriminant {half_b * half_b - a * c};

  if (discriminant < 0.0) return false;
  const auto sqrtd {glm::sqrt(discriminant)};

  auto root {(-half_b - sqrtd) / a};
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root) return false;
  }

  record.m_t = root;
  record.m_point = ray.at(record.m_t);
  const Vector outward_normal {(record.m_point - m_center) / m_radius};
  record.setFaceNormal(ray, outward_normal);
  record.m_material = m_material;

  return true;
}
