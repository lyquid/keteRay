#include "material.hpp"
#include "rectangle.hpp"
#include "scene.hpp"
#include "sphere.hpp"
#include "texture.hpp"
#include "../renderer/random.hpp"
#include <memory>

std::map<std::string, ktp::Scene> ktp::scenes {};

void ktp::scn::loadScenes() {
  Scene scene {};
  scene.m_name = k_DEFAULT_SCENE; // cover
  scene.m_background = {0.7, 0.8, 1.0};
  scene.m_function = cover;
  scene.m_world = cover();
  scenes.insert_or_assign(scene.m_name, scene);
  // checkered
  scene.m_name = "checkered";
  scene.m_background = {0.7, 0.8, 1.0};
  scene.m_function = checkered;
  scene.m_world = checkered();
  scenes.insert_or_assign(scene.m_name, scene);
  // earth
  scene.m_name = "earth";
  scene.m_background = {0.7, 0.8, 1.0};
  scene.m_function = earth;
  scene.m_world = earth();
  scenes.insert_or_assign(scene.m_name, scene);
  // 3 spheres
  scene.m_name = "3 spheres";
  scene.m_background = {0.7, 0.8, 1.0};
  scene.m_function = threeSpheres;
  scene.m_world = threeSpheres();
  scenes.insert_or_assign(scene.m_name, scene);
  // perlin
  scene.m_name = "perlin";
  scene.m_background = {0.7, 0.8, 1.0};
  scene.m_function = perlin;
  scene.m_world = perlin();
  scenes.insert_or_assign(scene.m_name, scene);
  // simple light
  scene.m_name = "simple light";
  scene.m_background = {0.0, 0.0, 0.0};
  scene.m_function = simpleLight;
  scene.m_world = simpleLight();
  scenes.insert_or_assign(scene.m_name, scene);
  // turbulence
  scene.m_name = "turbulence";
  scene.m_background = {0.7, 0.8, 1.0};
  scene.m_function = turbulence;
  scene.m_world = turbulence();
  scenes.insert_or_assign(scene.m_name, scene);
}

ktp::HittableList ktp::scn::checkered() {
  HittableList world {};
  const TexturePtr checker {std::make_shared<CheckerTexture>(Color(0.2, 0.3, 0.1), Color(0.9, 0.9, 0.9))};
  world.add(std::make_shared<Sphere>(Point(0,-10, 0), 10.0, std::make_shared<Lambertian>(checker)));
  world.add(std::make_shared<Sphere>(Point(0, 10, 0), 10.0, std::make_shared<Lambertian>(checker)));
  return world;
}

ktp::HittableList ktp::scn::cover() {
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
  // const MaterialPtr material2 {std::make_shared<DiffuseLight>(Color(100.0, 100.0, 100.0))};
  world.add(std::make_shared<Sphere>(Point(-4.0, 1.0, 0.0), 1.0, material2));

  const MaterialPtr material1 {std::make_shared<Dielectric>(1.5)};
  world.add(std::make_shared<Sphere>(Point(0.0, 1.0, 0.0), 1.0, material1));

  // const TexturePtr turbulence {std::make_shared<TurbulenceTexture>(4.0)};
  // const MaterialPtr material3 {std::make_shared<Metal>(turbulence, 0.0)};
  const MaterialPtr material3 {std::make_shared<Metal>(Color(0.7, 0.6, 0.5), 0.0)};
  world.add(std::make_shared<Sphere>(Point(4.0, 1.0, 0.0), 1.0, material3));

  return HittableList(std::make_shared<BVHnode>(world));
}

ktp::HittableList ktp::scn::earth() {
  const auto earth_texture {std::make_shared<ImageTexture>("resources/earthmario.jpg")};
  const auto earth_surface {std::make_shared<Lambertian>(earth_texture)};
  const auto globe {std::make_shared<Sphere>(Point(0.0, 0.0, 0.0), 2.0, earth_surface)};
  return HittableList(globe);
}

ktp::HittableList ktp::scn::perlin() {
  HittableList world {};
  const TexturePtr perlin {std::make_shared<NoiseTexture>(4.0)};
  world.add(std::make_shared<Sphere>(Point(0.0, -1000.0, 0.0), 1000.0, std::make_shared<Lambertian>(perlin)));
  world.add(std::make_shared<Sphere>(Point(0.0,     2.0, 0.0),    2.0, std::make_shared<Lambertian>(perlin)));
  return world;
}

ktp::HittableList ktp::scn::simpleLight() {
  HittableList world {};

  const auto perlin_tex {std::make_shared<NoiseTexture>(4)};
  world.add(std::make_shared<Sphere>(Point(0.0, -1000.0, 0.0), 1000.0, std::make_shared<Lambertian>(perlin_tex)));
  const auto earth_tex {std::make_shared<ImageTexture>("resources/earthmario.jpg")};
  world.add(std::make_shared<Sphere>(Point(0.0,     2.0, 0.0),    2.0, std::make_shared<Lambertian>(earth_tex)));

  const auto diff_light {std::make_shared<DiffuseLight>(Color(4.0, 4.0, 4.0))};
  world.add(std::make_shared<Rectangle>(3.0, 5.0, 1.0, 3.0, -2.0, diff_light));
  // world.add(std::make_shared<Sphere>(Point(0.0,     2.0, 0.0),    2.0, diff_light));

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

ktp::HittableList ktp::scn::turbulence() {
  HittableList world {};
  const TexturePtr turbulence {std::make_shared<TurbulenceTexture>(4.0)};
  world.add(std::make_shared<Sphere>(Point(0.0, -1000.0, 0.0), 1000.0, std::make_shared<Lambertian>(turbulence)));
  world.add(std::make_shared<Sphere>(Point(0.0,     2.0, 0.0),    2.0, std::make_shared<Lambertian>(turbulence)));
  return world;
}
