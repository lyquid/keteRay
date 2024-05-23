/**
 * @file config.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Json config file parser.
 * @version 0.1
 * @date 2022-10-28
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KETERAY_SRC_CONFIG_HPP_
#define KETERAY_SRC_CONFIG_HPP_

#include "types.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

namespace ktp {

using json = nlohmann::json;

struct RenderConfig {
  int         m_samples {100};
  std::string m_scene_name {k_DEFAULT_SCENE};
  int         m_width {400};
};

inline Vector jsonVectorToVector(json v) {
  return Vector { v[0], v[1], v[2] };
}

void parseConfigFile(CameraConfig& camera_config, RenderConfig& render_config);

} // namespace ktp

#endif
