/**
 * @file hittable.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief An interface for hittable objects.
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KETERAY_SRC_WORLD_HITTABLE_HPP_
#define KETERAY_SRC_WORLD_HITTABLE_HPP_

#include "world_types.hpp"
#include "../renderer/types.hpp"
#include <vector>

namespace ktp {

struct HitRecord {
  bool        m_front_face {};
  MaterialPtr m_material {nullptr};
  Vector      m_normal {};
  Point       m_point {};
  double      m_t {};
  double      m_u {};
  double      m_v {};

  void setFaceNormal(const Ray& ray, const Vector& outward_normal);
};

class AABB {
 public:

  AABB() = default;
  AABB(const Point& min, const Point& max): m_max(max), m_min(min) {}

  static AABB surroundingBox(const AABB& box0, const AABB& box1);

  bool hit(const Ray& ray, double t_min, double t_max) const;
  auto max() const {return m_max; }
  auto min() const {return m_min; }

 private:

  Point m_max {};
  Point m_min {};
};

class Hittable {
 public:
  virtual ~Hittable() {}
  virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const = 0;
  virtual bool boundingBox(AABB& output_box) const = 0;
};

class HittableList: public Hittable {

  friend class BVHnode;

 public:

  HittableList() = default;
  HittableList(HittablePtr object) { add(object); }

  void add(HittablePtr object) { m_objects.push_back(object); }
  bool boundingBox(AABB& output_box) const override;
  void clear() { m_objects.clear(); }
  bool hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const override;

 private:

  std::vector<HittablePtr> m_objects {};
};

// Bounding Volume Hierarchy
class BVHnode: public Hittable {
 public:

  BVHnode(const HittableList& list): BVHnode(list.m_objects, 0, list.m_objects.size()) {}
  BVHnode(const std::vector<HittablePtr>& src_objects, size_t start, size_t end);

  bool boundingBox(AABB& output_box) const override {
    output_box = m_box;
    return true;
  }
  bool hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const override;

 private:

  AABB m_box {};
  HittablePtr m_left {nullptr};
  HittablePtr m_right {nullptr};
};

} // namespace ktp

#endif
