#include "hittable.hpp"
#include "material.hpp"
#include "../renderer/random.hpp"
#include "../renderer/ray.hpp"

bool ktp::Lambertian::scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const {
  Vector scatter_direction {record.m_normal + rng::randomUnitVector()};
  // degenerate scatter direction
  if (nearZero(scatter_direction)) {
    scatter_direction = record.m_normal;
  }
  scattered = Ray(record.m_point, scatter_direction);
  attenuation = m_albedo;
  return true;
}

bool ktp::Metal::scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const {
  Vector reflected {reflect(glm::normalize(ray.direction()), record.m_normal)};
  scattered = Ray(record.m_point, reflected + m_fuzz * rng::randomInUnitSphere());
  attenuation = m_albedo;
  return (glm::dot(scattered.direction(), record.m_normal) > 0.0);
}

double ktp::Dielectric::reflectance(double cosine, double ref_idx) {
  // use Schlick's approximation for reflectance
  auto r0 {(1 - ref_idx) / (1 + ref_idx)};
  r0 = r0 * r0;
  return r0 + (1.0 - r0) * glm::pow((1.0 - cosine), 5.0);
}

bool ktp::Dielectric::scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const {
  attenuation = Color(1.0, 1.0, 1.0);
  const auto refraction_ratio {record.m_front_face ? 1.0 / m_ir : m_ir};

  const Vector unit_direction {glm::normalize(ray.direction())};
  const auto cos_theta {fmin(glm::dot(-unit_direction, record.m_normal), 1.0)};
  const auto sin_theta {glm::sqrt(1.0 - cos_theta * cos_theta)};

  const bool cannot_refract {refraction_ratio * sin_theta > 1.0};
  Vector direction {};
  if (cannot_refract || reflectance(cos_theta, refraction_ratio) > rng::randomDouble()) {
    direction = reflect(unit_direction, record.m_normal);
  } else {
    direction = refract(unit_direction, record.m_normal, refraction_ratio);
  }
  scattered = Ray(record.m_point, direction);

  return true;
}
