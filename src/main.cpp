#include "renderer/camera.hpp"
#include "config.hpp"
// #include "gui/gui.hpp"
#include "world/hittable.hpp"
#include "./renderer/keteray.hpp"
#include "world/material.hpp"
#include "world/scene.hpp"
#include "world/sphere.hpp"
#include <algorithm> // find
#include <memory>
#include <thread> // to delete when gui works

using StringsVector = std::vector<std::string>;
void processArgs(const StringsVector& args, ktp::RenderConfig& render_config);

int main(int argc, char* argv[]) {
  using namespace ktp;
  // scenes
  loadScenes();
  // config file
  CameraConfig camera_config {};
  FileConfig   file_config {};
  RenderConfig render_config {};
  parseConfigFile(camera_config, file_config, render_config);
  // args processing
  processArgs(StringsVector(argv, argv + argc), render_config);
  // camera
  Camera camera {camera_config};
  // render data
  RenderData render_data {};
  render_data.m_camera = &camera;
  render_data.m_width = render_config.m_width;
  render_data.m_height = static_cast<int>(render_data.m_width / camera.aspectRatio());
  render_data.m_samples_per_pixel = render_config.m_samples;
  render_data.m_scene = scenes[render_config.m_scene];
  // image data
  ppm::PPMFileData file_data {};
  file_data.m_name = file_config.m_name;
  file_data.m_file_name = createFileName(render_data, file_data);
  // GUI
  // gui::start(&render_data, &camera_config, &file_data);
  // render **to delete**
  std::cout << "Begin rendering at " << render_data.m_width << 'x' << render_data.m_height
            << '@' << render_data.m_samples_per_pixel << "spp.\n";
  std::thread render_thread {[&] {
    int progress {};
    keteRay(render_data, file_data, progress);
    ppm::makePPMFile(file_data);
  }};
  render_thread.join();

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
