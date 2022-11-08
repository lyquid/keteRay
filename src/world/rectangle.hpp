/**
 * @file rectangle.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Rectangle class.
 * @version 0.1
 * @date 2022-11-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KETERAY_SRC_WORLD_RECTANGLE_HPP_
#define KETERAY_SRC_WORLD_RECTANGLE_HPP_

#include "hittable.hpp"

namespace ktp {

class Rectangle: public Hittable {
 public:

  Rectangle() = default;
  Rectangle(double x0, double x1, double y0, double y1, double k, MaterialPtr mat):
    m_x0(x0), m_x1(x1), m_y0(y0), m_y1(y1), m_k(k), m_material(mat) {};

  bool boundingBox(AABB& output_box) const override;
  bool hit(const Ray& ray, double t_min, double t_max, HitRecord& record) const override;

 private:

  MaterialPtr m_material {nullptr};
  double m_x0{}, m_x1{}, m_y0{}, m_y1{}, m_k{};
};

} // namespace ktp

#endif
