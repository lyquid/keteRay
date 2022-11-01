#include "renderer/camera.hpp"
#include "config.hpp"
#include "gui/gui.hpp"
#include "world/hittable.hpp"
#include "./renderer/keteray.hpp"
#include "world/material.hpp"
#include "world/scene.hpp"
#include "world/sphere.hpp"
#include <algorithm> // find
#include <memory>

using StringsVector = std::vector<std::string>;
void processArgs(const StringsVector& args, ktp::RenderConfig& render_config);

int main(int argc, char* argv[]) {
  using namespace ktp;
  // config file
  CameraConfig camera_config {};
  FileConfig   file_config {};
  RenderConfig render_config {};
  parseConfigFile(camera_config, file_config, render_config);
  // args processing
  processArgs(StringsVector(argv, argv + argc), render_config);
  // camera
  Camera camera {camera_config};
  // world
  HittableList world {randomScene()};
  // const MaterialPtr material_ground {std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0))};
  // const MaterialPtr material_center {std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3))};
  // const MaterialPtr material_left   {std::make_shared<Dielectric>(1.5)};
  // const MaterialPtr material_right  {std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.5)};
  // world.add(std::make_shared<Sphere>(Point( 0.0, -100.5, -1.0), 100.0, material_ground));
  // world.add(std::make_shared<Sphere>(Point( 0.0,    0.0, -1.0),   0.5, material_center));
  // world.add(std::make_shared<Sphere>(Point(-1.0,    0.0, -1.0),  -0.5, material_left));
  // world.add(std::make_shared<Sphere>(Point( 1.0,    0.0, -1.0),   0.5, material_right));
  // render data
  RenderData render_data {};
  render_data.m_camera = &camera;
  render_data.m_width = render_config.m_width;
  render_data.m_height = static_cast<int>(render_data.m_width / camera.aspectRatio());
  render_data.m_samples_per_pixel = render_config.m_samples;
  render_data.m_world = &world;
  // image data
  ppm::PPMFileData file_data {};
  file_data.m_name = file_config.m_name;
  file_data.m_file_name = createFileName(render_data, file_data);
  // GUI
  gui::start(&render_data, &camera_config, &file_data);

  return 0;
}

void processArgs(const StringsVector& args, ktp::RenderConfig& render_config) {
  for (const auto& arg: args) {
    if (arg.find("samples") != std::string::npos
     || arg.find("-s")      != std::string::npos) {
      render_config.m_samples = std::stoi(arg.substr(arg.find("=") + 1));
      continue;
    }
    if (arg.find("width") != std::string::npos
     || arg.find("-w")    != std::string::npos) {
      render_config.m_width = std::stoi(arg.substr(arg.find("=") + 1));
      continue;
    }
  }
}
