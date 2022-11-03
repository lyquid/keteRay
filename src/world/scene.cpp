#include "hittable.hpp"
#include "material.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "../renderer/keteray.hpp"
#include "../renderer/random.hpp"
#include <memory>

ktp::HittableList ktp::randomScene() {
  HittableList world {};

  const auto ground_material {std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5))};
  world.add(std::make_shared<Sphere>(Point(0.0, -1000.0, 0.0), 1000.0, ground_material));

  for (int a = -11; a < 11; ++a) {
    for (int b = -11; b < 11; ++b) {
      const auto choose_mat {rng::randomDouble()};
      const Point center {a + 0.9 * rng::randomDouble(), 0.2, b + 0.9 * rng::randomDouble()};

      if ((center - Point(4.0, 0.2, 0.0)).length() > 0.9) {
        std::shared_ptr<Material> sphere_material {nullptr};

        if (choose_mat < 0.8) {
          // diffuse
          const auto albedo {rng::randomColor() * rng::randomColor()};
          sphere_material = std::make_shared<Lambertian>(albedo);
          world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
        } else if (choose_mat < 0.95) {
          // metal
          const auto albedo {rng::randomColor(0.5, 1.0)};
          const auto fuzz {rng::randomDouble(0.0, 0.5)};
          sphere_material = std::make_shared<Metal>(albedo, fuzz);
          world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = std::make_shared<Dielectric>(1.5);
          world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  const auto material1 {std::make_shared<Dielectric>(1.5)};
  world.add(std::make_shared<Sphere>(Point(0.0, 1.0, 0.0), 1.0, material1));

  const auto material2 {std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1))};
  world.add(std::make_shared<Sphere>(Point(-4.0, 1.0, 0.0), 1.0, material2));

  const auto material3 {std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0)};
  world.add(std::make_shared<Sphere>(Point(4.0, 1.0, 0.0), 1.0, material3));

  return HittableList(std::make_shared<BVHnode>(world));
}
