#include "hittable.hpp"
#include "../renderer/keteray.hpp"
#include "../renderer/ray.hpp"
#include <algorithm> // std::swap

// AABB

bool ktp::AABB::hit(const Ray& ray, double t_min, double t_max) const {
  for (int i = 0; i < 3; ++i) {
    const auto inv_dir {1.0 / ray.direction()[i]};
    auto t0 {(m_min[i] - ray.origin()[i]) * inv_dir};
    auto t1 {(m_max[i] - ray.origin()[i]) * inv_dir};
    if (inv_dir < 0.0) std::swap(t0, t1);
    t_min = t0 > t_min ? t0 : t_min;
    t_max = t1 < t_max ? t1 : t_max;
    if (t_max <= t_min) return false;
  }
  return true;
}

ktp::AABB ktp::AABB::surroundingBox(const AABB& box0, const AABB& box1) {
  const Point small{
    fmin(box0.min().x, box1.min().x),
    fmin(box0.min().y, box1.min().y),
    fmin(box0.min().z, box1.min().z)
  };
  const Point big{
    fmax(box0.max().x, box1.max().x),
    fmax(box0.max().y, box1.max().y),
    fmax(box0.max().z, box1.max().z)
  };
  return AABB{small, big};
}

// BVHnode

inline bool boxCompare(const ktp::HittablePtr a, const ktp::HittablePtr b, int axis) {
  ktp::AABB box_a {};
  ktp::AABB box_b {};

  if (!a->boundingBox(box_a) || !b->boundingBox(box_b))
    std::cerr << "No bounding box in bvh_node constructor.\n";

  return box_a.min()[axis] < box_b.min()[axis];
}

inline bool boxCompareX(const ktp::HittablePtr a, const ktp::HittablePtr b) { return boxCompare(a, b, 0); }
inline bool boxCompareY(const ktp::HittablePtr a, const ktp::HittablePtr b) { return boxCompare(a, b, 1); }
inline bool boxCompareZ(const ktp::HittablePtr a, const ktp::HittablePtr b) { return boxCompare(a, b, 2); }

ktp::BVHnode::BVHnode(const std::vector<HittablePtr>& src_objects, size_t start, size_t end) {
  auto objects {src_objects};
  const int axis {randomInt(0, 2)};
  const auto comparator {(axis == 0) ? boxCompareX
                       : (axis == 1) ? boxCompareY : boxCompareZ};

  const size_t object_span {end - start};

  if (object_span == 1) {
    m_left = m_right = objects[start];
  } else if (object_span == 2) {
    if (comparator(objects[start], objects[start + 1])) {
      m_left = objects[start];
      m_right = objects[start + 1];
    } else {
      m_left = objects[start + 1];
      m_right = objects[start];
    }
  } else {
    std::sort(objects.begin() + start, objects.begin() + end, comparator);

    const auto mid {start + object_span / 2};
    m_left = std::make_shared<BVHnode>(objects, start, mid);
    m_right = std::make_shared<BVHnode>(objects, mid, end);
  }

  AABB box_left {}, box_right {};

  if (!m_left->boundingBox(box_left) || !m_right->boundingBox(box_right))
    std::cerr << "No bounding box in bvh_node constructor.\n";

  m_box = AABB::surroundingBox(box_left, box_right);
}

bool ktp::BVHnode::hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const {
  if (!m_box.hit(ray, t_min, t_max)) return false;

  const bool hit_left {m_left->hit(ray, t_min, t_max, record)};
  const bool hit_right {m_right->hit(ray, t_min, hit_left ? record.m_t : t_max, record)};

  return hit_left || hit_right;
}

// HITTRECORD

void ktp::HitRecord::setFaceNormal(const Ray& ray, const Vector& outward_normal) {
  m_front_face = glm::dot(ray.direction(), outward_normal) < 0.0;
  m_normal = m_front_face ? outward_normal : -outward_normal;
}

// HITTABLE

bool ktp::HittableList::boundingBox(AABB& output_box) const {
  if (m_objects.empty()) return false;

  AABB temp_box {};
  bool first_box {true};

  for (const auto& object: m_objects) {
    if (!object->boundingBox(temp_box)) return false;
    output_box = first_box ? temp_box : AABB::surroundingBox(output_box, temp_box);
    first_box = false;
  }

  return true;
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
