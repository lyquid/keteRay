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

struct CameraConfig;

struct FileConfig {
  std::string m_name {"render"};
};

struct RenderConfig {
  int m_samples {100};
  int m_width {400};
};

inline Vector jsonVectorToVector(nlohmann::json_abi_v3_11_2::json v) {
  return Vector { v[0], v[1], v[2] };
}

void parseConfigFile(CameraConfig& camera_config, FileConfig& file_config, RenderConfig& render_config);

} // namespace ktp

#endif
