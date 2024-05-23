#include "../renderer/ray.hpp"
#include "sphere.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp> // glm::dot, glm::length2
#include <glm/gtc/constants.hpp> // glm::pi
#include <cmath>

void ktp::Sphere::getSphereUV(const Point& p, double& u, double& v) {
  // p: a given point on the sphere of radius one, centered at the origin.
  // u: returned value [0,1] of angle around the Y axis from X=-1.
  // v: returned value [0,1] of angle from Y=-1 to Y=+1.
  //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
  //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
  //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

  const auto theta {glm::acos(-p.y)};
  const auto phi {std::atan2(-p.z, p.x) + glm::pi<double>()};

  u = phi / (glm::two_pi<double>());
  v = theta / glm::pi<double>();
}

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
  getSphereUV(outward_normal, record.m_u, record.m_v);
  record.m_material = m_material;

  return true;
}
