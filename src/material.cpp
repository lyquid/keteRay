#include "hittable.hpp"
#include "material.hpp"
#include "ray.hpp"

bool ktp::Lambertian::scatter(const Ray& ray, const HitRecord& record, Color& attenuation, Ray& scattered) const {
  Vector scatter_direction {record.m_normal + randomUnitVector()};
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
  scattered = Ray(record.m_point, reflected + m_fuzz * randomInUnitSphere());
  attenuation = m_albedo;
  return (glm::dot(scattered.direction(), record.m_normal) > 0.0);
}
