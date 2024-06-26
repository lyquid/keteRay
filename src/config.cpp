#include "config.hpp"
#include "renderer/camera.hpp"
#include "world/scene.hpp"
#include <algorithm> // std::transform
#include <cctype> // std::tolower

#ifndef __GNUC__
void ktp::parseConfigFile(CameraConfig& camera_config, RenderConfig& render_config) {
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
  // render
  render_config.m_samples = config["render"]["samples"];
  std::string req_scene {config["render"]["scene"]};
  std::transform(req_scene.begin(), req_scene.end(), req_scene.begin(),
    [](unsigned char c){ return std::tolower(c); });
  if (scenes.find(req_scene) != scenes.end()) {
    // scene found
    render_config.m_scene_name = req_scene;
    // scenes[req_scene].m_background = jsonVectorToVector(config["render"]["backgroundColor"]);
  } else {
    // scene not found
    std::cout << "Requested scene NOT found. Check your config file!\n";
  }
  render_config.m_width = config["render"]["width"];
}
#endif

#ifdef __GNUC__
void ktp::parseConfigFile(CameraConfig& camera_config, RenderConfig& render_config) {
  std::ifstream file {"config.json"};
  const json config {json::parse(file)};
  // camera
  const double w {config[0]["camera"]["aspectRatio"]["w"]}, h {config[0]["camera"]["aspectRatio"]["h"]};
  camera_config.m_aspect_ratio = w / h;
  camera_config.m_look_at    = jsonVectorToVector(config[0]["camera"]["lookAt"]);
  camera_config.m_look_from  = jsonVectorToVector(config[0]["camera"]["lookFrom"]);
  camera_config.m_vertical   = jsonVectorToVector(config[0]["camera"]["vertical"]);
  camera_config.m_vfov       = config[0]["camera"]["vFov"];
  camera_config.m_aperture   = config[0]["camera"]["aperture"];
  camera_config.m_focus_dist = config[0]["camera"]["focusDist"];
  // render
  render_config.m_samples = config[0]["render"]["samples"];
  std::string req_scene {config[0]["render"]["scene"]};
  std::transform(req_scene.begin(), req_scene.end(), req_scene.begin(),
    [](unsigned char c){ return std::tolower(c); });
  if (scenes.find(req_scene) != scenes.end()) {
    // scene found
    render_config.m_scene_name = req_scene;
    // scenes[req_scene].m_background = jsonVectorToVector(config[0]["render"]["backgroundColor"]);
  } else {
    // scene not found
    std::cout << "Requested scene NOT found. Check your config file!\n";
  }
  render_config.m_width = config[0]["render"]["width"];
}
#endif
