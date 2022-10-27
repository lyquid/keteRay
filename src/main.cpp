#include "camera.hpp"
#include "hittable.hpp"
#include "keteray.hpp"
#include "material.hpp"
#include "ray.hpp"
#include "sphere.hpp"
#include <algorithm>
#include <memory>

struct Args {
  std::string m_file_name {"render"};
  int         m_samples {100};
  int         m_width {400};
};

using StringsVector = std::vector<std::string>;
Args processArgs(const StringsVector& args);

int main(int argc, char* argv[]) {
  // args processing
  const Args args {processArgs(StringsVector(argv, argv + argc))};
  // camera
  ktp::Camera camera {};
  // image data
  ppm::PPMFileData file_data {};
  file_data.m_width  = args.m_width;
  file_data.m_height = static_cast<int>(file_data.m_width / camera.aspectRatio());
  file_data.m_pixels.reserve(file_data.m_width * file_data.m_height);
  file_data.m_name = args.m_file_name    + "_"
    + std::to_string(file_data.m_width)  + "x"
    + std::to_string(file_data.m_height) + "_"
    + std::to_string(args.m_samples)     + "_samples.ppm";
  // world
  ktp::HittableList world {};
  const ktp::MaterialPtr material_ground {std::make_shared<ktp::Lambertian>(ktp::Color(0.8, 0.8, 0.0))};
  const ktp::MaterialPtr material_center {std::make_shared<ktp::Lambertian>(ktp::Color(0.7, 0.3, 0.3))};
  const ktp::MaterialPtr material_left   {std::make_shared<ktp::Metal>(ktp::Color(0.8, 0.8, 0.8))};
  const ktp::MaterialPtr material_right  {std::make_shared<ktp::Metal>(ktp::Color(0.8, 0.6, 0.2))};
  world.add(std::make_shared<ktp::Sphere>(ktp::Point( 0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(std::make_shared<ktp::Sphere>(ktp::Point( 0.0,    0.0, -1.0),   0.5, material_center));
  world.add(std::make_shared<ktp::Sphere>(ktp::Point(-1.0,    0.0, -1.0),   0.5, material_left));
  world.add(std::make_shared<ktp::Sphere>(ktp::Point( 1.0,    0.0, -1.0),   0.5, material_right));
  // render data
  ktp::RenderData render_data {};
  render_data.m_camera = &camera;
  render_data.m_samples_per_pixel = args.m_samples;
  render_data.m_world = &world;
  // render
  std::cout << "Begin rendering at " << file_data.m_width << 'x' << file_data.m_height
            << '@' << render_data.m_samples_per_pixel << "spp.\n";
  ktp::keteRay(render_data, file_data);
  // file generation
  ppm::makePPMFile(file_data);

  return 0;
}

Args processArgs(const StringsVector& args) {
  Args processed_args {};
  for (const auto& arg: args) {
    if (arg.find("samples") != std::string::npos
     || arg.find("-s")      != std::string::npos) {
      processed_args.m_samples = std::stoi(arg.substr(arg.find("=") + 1));
      continue;
    }
    if (arg.find("width") != std::string::npos
     || arg.find("-w")    != std::string::npos) {
      processed_args.m_width = std::stoi(arg.substr(arg.find("=") + 1));
      continue;
    }
  }
  return processed_args;
}
