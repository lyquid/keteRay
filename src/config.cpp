#include "camera.hpp"
#include "config.hpp"

void ktp::parseConfigFile(CameraConfig& camera_config, FileConfig& file_config, RenderConfig& render_config) {
  std::ifstream file {"config.json"};
  const json config {json::parse(file)};
  // camera
  const double w {config["camera"]["aspectRatio"]["w"]}, h {config["camera"]["aspectRatio"]["h"]};
  camera_config.m_aspect_ratio = w / h;
  camera_config.m_look_at    = jsonVectorToVector(config["camera"]["lookAt"]);
  camera_config.m_look_from  = jsonVectorToVector(config["camera"]["lookFrom"]);
  camera_config.m_vertical   = jsonVectorToVector(config["camera"]["vertical"]);
  camera_config.m_vfov       = config["camera"]["vFov"];
  camera_config.m_aperture   = config["camera"]["aperture"];
  camera_config.m_focus_dist = config["camera"]["focusDist"];
  // file
  file_config.m_name = config["file"]["name"];
  // render
  render_config.m_samples = config["render"]["samples"];
  render_config.m_width   = config["render"]["width"];
}
