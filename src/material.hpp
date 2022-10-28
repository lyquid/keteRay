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
  Metal(const Color& albedo, double fuzz = 0.0):
    m_albedo(albedo),
    m_fuzz(fuzz < 1.0 ? fuzz : 1.0) {}
  bool scatter(
    const Ray& ray,
    const HitRecord& record,
    Color& attenuation,
    Ray& scattered
  ) const override;
 private:
  Color  m_albedo {};
  double m_fuzz {};
};

class Dielectric: public Material {
 public:
  Dielectric(double index_of_refraction): m_ir(index_of_refraction) {}
  bool scatter(
    const Ray& ray,
    const HitRecord& record,
    Color& attenuation,
    Ray& scattered
  ) const override;
 private:
  static double reflectance(double cosine, double ref_idx);
  double m_ir {};
};

} // namespace ktp

#endif
