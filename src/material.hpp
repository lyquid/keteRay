/**
 * @file material.hpp
 * @author your name (alexcastilloblanco@gmail.com)
 * @brief An abstract class for materials.
 * @version 0.1
 * @date 2022-10-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KTP_MATERIAL_HPP_
#define KTP_MATERIAL_HPP_

#include "keteray.hpp"
#include <memory>

namespace ktp {

class HitRecord;
class Ray;

class Material {
 public:
  virtual ~Material() {}
  virtual bool scatter(
    const Ray& ray,
    const HitRecord& record,
    Color& attenuation,
    Ray& scattered
  )  const = 0;
};

class Lambertian: public Material {
 public:
  Lambertian(const Color& albedo): m_albedo(albedo) {}
  bool scatter(
    const Ray& ray,
    const HitRecord& record,
    Color& attenuation,
    Ray& scattered
  ) const override;
 private:
  Color m_albedo {};
};

class Metal: public Material {
 public:
  Metal(const Color& albedo): m_albedo(albedo) {}
  bool scatter(
    const Ray& ray,
    const HitRecord& record,
    Color& attenuation,
    Ray& scattered
  ) const override;
 private:
  Color m_albedo {};
};

} // namespace ktp

#endif
