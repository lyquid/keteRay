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

#ifndef KETERAY_SRC_WORLD_MATERIAL_HPP_
#define KETERAY_SRC_WORLD_MATERIAL_HPP_

#include "texture.hpp"
#include "../types.hpp"

namespace ktp {

class Material {
 public:
  virtual ~Material() {}
  virtual Color emitted(double u, double v, const Point& p) const {
    return Color(0.0, 0.0, 0.0);
  }
  virtual bool scatter(
    const Ray& ray,
    const HitRecord& record,
    Color& attenuation,
    Ray& scattered
  )  const = 0;
};

class DiffuseLight: public Material {
 public:
  DiffuseLight(TexturePtr texture): m_emit(texture) {}
  DiffuseLight(Color color): m_emit(std::make_shared<SolidColorTexture>(color)) {}
  bool scatter(
    const Ray& ray,
    const HitRecord& record,
    Color& attenuation,
    Ray& scattered
  ) const override { return false; }
  virtual Color emitted(double u, double v, const Point& p) const override {
    return m_emit->value(u, v, p);
  }
 private:
  TexturePtr m_emit {nullptr};
};

class Lambertian: public Material {
 public:
  Lambertian(const Color& albedo): m_albedo(std::make_shared<SolidColorTexture>(albedo)) {}
  Lambertian(TexturePtr albedo): m_albedo(albedo) {}
  bool scatter(
    const Ray& ray,
    const HitRecord& record,
    Color& attenuation,
    Ray& scattered
  ) const override;
 private:
  TexturePtr m_albedo {nullptr};
};

class Metal: public Material {
 public:
  Metal(const Color& albedo, double fuzz = 0.0):
    Metal(std::make_shared<SolidColorTexture>(albedo), fuzz) {}
  Metal(TexturePtr albedo, double fuzz = 0.0):
    m_albedo(albedo),
    m_fuzz(fuzz < 1.0 ? fuzz : 1.0) {}
  bool scatter(
    const Ray& ray,
    const HitRecord& record,
    Color& attenuation,
    Ray& scattered
  ) const override;
 private:
  TexturePtr m_albedo {nullptr};
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
