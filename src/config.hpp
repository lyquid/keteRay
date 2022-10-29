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

#ifndef KTP_CONFIG_HPP_
#define KTP_CONFIG_HPP_

#include "keteray.hpp"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

namespace ktp {

using json = nlohmann::json;

struct CameraConfig {
  double m_aperture {1.0};
  double m_aspect_ratio {16.0 / 9.0};
  double m_focus_dist {0.0};
  Vector m_look_at   {0.0, 0.0, -1.0};
  Vector m_look_from {0.0, 0.0,  0.0};
  Vector m_vertical  {0.0, 1.0,  0.0};
  double m_vfov {90.0};
};

struct RenderConfig {
  std::string m_file_name {"render"};
  int         m_samples {100};
  int         m_width {400};
};

inline Vector jsonVectorToVector(nlohmann::json_abi_v3_11_2::json v) {
  return Vector {v[0], v[1], v[2] };
}

void parseConfigFile(CameraConfig& camera_config, RenderConfig& render_config);

} // namespace ktp

#endif
