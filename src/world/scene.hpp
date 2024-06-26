/**
 * @file scene.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Random scene generation.
 * @version 0.1
 * @date 2022-10-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KETERAY_SRC_WORLD_SCENE_HPP_
#define KETERAY_SRC_WORLD_SCENE_HPP_

#include "hittable.hpp"
#include "../types.hpp"
#include <functional>
#include <map>
#include <string>
#include <vector>

namespace ktp {

struct Scene {
  Color m_background {};
  std::function<HittableList()> m_function {};
  std::string m_name {};
  HittableList m_world {};
};

namespace scn {
  void loadScenes();
  TexturePtr randomTexture();
  HittableList checkered();
  HittableList cover();
  HittableList earth();
  HittableList marble();
  HittableList perlin();
  HittableList simpleLight();
  HittableList threeSpheres();
  HittableList turbulence();
}

extern std::map<std::string, Scene> scenes;

} // namespace ktp

#endif
