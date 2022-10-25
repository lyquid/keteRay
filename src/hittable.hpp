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

#ifndef HITTABLE_HPP_
#define HITTABLE_HPP_

#include "owert.hpp"
#include <memory>
#include <vector>

namespace ktp {

class Ray;

struct HitRecord {
  bool   m_front_face {};
  Vector m_normal {};
  Point  m_point {};
  double m_t {};

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
  HittableList(std::shared_ptr<Hittable> object) { add(object); }

  void add(std::shared_ptr<Hittable> object) { m_objects.push_back(object); }
  void clear() { m_objects.clear(); }
  bool hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const override;

 private:
  std::vector<std::shared_ptr<Hittable>> m_objects {};
};

} // namespace ktp

#endif
