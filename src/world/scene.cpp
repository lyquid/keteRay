#include "material.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "../renderer/random.hpp"
#include <memory>

std::map<std::string, ktp::Scene> ktp::scenes {};

void ktp::scn::loadScenes() {
  scenes.insert_or_assign(k_DEFAULT_SCENE, Scene{scn::coverScene, scn::coverScene()});
  scenes.insert_or_assign("checkered spheres", Scene{scn::checkeredSpheresScene, scn::checkeredSpheresScene()});
  scenes.insert_or_assign("3 spheres", Scene{scn::threeSpheres, scn::threeSpheres()});
  scenes.insert_or_assign("perlin spheres", Scene{scn::perlinSpheres, scn::perlinSpheres()});
}

ktp::HittableList ktp::scn::checkeredSpheresScene() {
  HittableList world {};
  const TexturePtr checker {std::make_shared<CheckerTexture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9))};
  world.add(std::make_shared<Sphere>(Point(0,-10, 0), 10.0, std::make_shared<Lambertian>(checker)));
  world.add(std::make_shared<Sphere>(Point(0, 10, 0), 10.0, std::make_shared<Lambertian>(checker)));
  return world;
}

ktp::HittableList ktp::scn::coverScene() {
  HittableList world {};

  const TexturePtr checker {std::make_shared<CheckerTexture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9))};
  const MaterialPtr ground_material {std::make_shared<Lambertian>(checker)};
  // const auto ground_material {std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5))};
  world.add(std::make_shared<Sphere>(Point(0.0, -1000.0, 0.0), 1000.0, ground_material));

  for (int a = -11; a < 11; ++a) {
    for (int b = -11; b < 11; ++b) {
      const auto choose_mat {rng::randomDouble()};
      const Point center {a + 0.9 * rng::randomDouble(), 0.2, b + 0.9 * rng::randomDouble()};

      if ((center - Point(4.0, 0.2, 0.0)).length() > 0.9) {
        MaterialPtr sphere_material {nullptr};

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

  const MaterialPtr material2 {std::make_shared<Lambertian>(Color(0.4, 0.2, 0.1))};
  world.add(std::make_shared<Sphere>(Point(-4.0, 1.0, 0.0), 1.0, material2));

  const MaterialPtr material1 {std::make_shared<Dielectric>(1.5)};
  world.add(std::make_shared<Sphere>(Point(0.0, 1.0, 0.0), 1.0, material1));

  const MaterialPtr material3 {std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0)};
  world.add(std::make_shared<Sphere>(Point(4.0, 1.0, 0.0), 1.0, material3));

  return HittableList(std::make_shared<BVHnode>(world));
}

ktp::HittableList ktp::scn::perlinSpheres() {
  HittableList world {};
  const TexturePtr perlin {std::make_shared<NoiseTexture>(4.0)};
  world.add(std::make_shared<Sphere>(Point(0.0, -1000.0, 0.0), 1000.0, std::make_shared<Lambertian>(perlin)));
  world.add(std::make_shared<Sphere>(Point(0.0,     2.0, 0.0),    2.0, std::make_shared<Lambertian>(perlin)));
  return world;
}

ktp::HittableList ktp::scn::threeSpheres() {
  HittableList world {};
  const MaterialPtr material_ground {std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0))};
  const MaterialPtr material_center {std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3))};
  const MaterialPtr material_left   {std::make_shared<Dielectric>(1.5)};
  const MaterialPtr material_right  {std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.5)};
  world.add(std::make_shared<Sphere>(Point( 0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(std::make_shared<Sphere>(Point( 0.0,    0.0, -1.0),   0.5, material_center));
  world.add(std::make_shared<Sphere>(Point(-1.0,    0.0, -1.0),  -0.5, material_left));
  world.add(std::make_shared<Sphere>(Point( 1.0,    0.0, -1.0),   0.5, material_right));
  // return HittableList(std::make_shared<BVHnode>(world)); // this doesn't work
  return world;
}
