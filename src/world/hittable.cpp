#include "hittable.hpp"
#include "../renderer/ray.hpp"

void ktp::HitRecord::setFaceNormal(const Ray& ray, const Vector& outward_normal) {
  m_front_face = glm::dot(ray.direction(), outward_normal) < 0.0;
  m_normal = m_front_face ? outward_normal : -outward_normal;
}

bool ktp::HittableList::hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const {
  HitRecord tmp_record {};
  bool hit_anything {};
  auto closest_so_far {t_max};

  for (const auto& object: m_objects) {
    if (object->hit(ray, t_min, closest_so_far, tmp_record)) {
      hit_anything = true;
      closest_so_far = tmp_record.m_t;
      record = tmp_record;
    }
  }
  return hit_anything;
}
