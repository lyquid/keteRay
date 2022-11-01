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

#ifndef KTP_HITTABLE_HPP_
#define KTP_HITTABLE_HPP_

#include "../renderer/keteray.hpp"
#include <memory>
#include <vector>

namespace ktp {

class Material;
class Ray;

using HittablePtr = std::shared_ptr<Hittable>;
using MaterialPtr = std::shared_ptr<Material>;

struct HitRecord {
  bool        m_front_face {};
  MaterialPtr m_material {nullptr};
  Vector      m_normal {};
  Point       m_point {};
  double      m_t {};

  void setFaceNormal(const Ray& ray, const Vector& outward_normal);
};

class Hittable {
 public:
  virtual ~Hittable() {}
  virtual bool hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const = 0;
};

class HittableList: public Hittable {
 public:
  HittableList() = default;
  HittableList(HittablePtr object) { add(object); }

  void add(HittablePtr object) { m_objects.push_back(object); }
  void clear() { m_objects.clear(); }
  bool hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const override;

 private:
  std::vector<HittablePtr> m_objects {};
};

} // namespace ktp

#endif
