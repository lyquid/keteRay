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
  int         m_width {1400};
};

using StringsVector = std::vector<std::string>;
Args processArgs(const StringsVector& args);

int main(int argc, char* argv[]) {
  using namespace ktp;
  // args processing
  const Args args {processArgs(StringsVector(argv, argv + argc))};
  // camera
  Camera camera {};
  // Camera camera {Point(2, 2, 1), Point(0, 0, -1), Vector(0, 1, 0), 90.0};
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
  HittableList world {};
  const MaterialPtr material_ground {std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0))};
  const MaterialPtr material_center {std::make_shared<Lambertian>(Color(0.7, 0.3, 0.3))};
  const MaterialPtr material_left   {std::make_shared<Dielectric>(1.5)};
  const MaterialPtr material_right  {std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.5)};
  world.add(std::make_shared<Sphere>(Point( 0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(std::make_shared<Sphere>(Point( 0.0,    0.0, -1.0),   0.5, material_center));
  world.add(std::make_shared<Sphere>(Point(-1.0,    0.0, -1.0),   0.5, material_left));
  world.add(std::make_shared<Sphere>(Point( 1.0,    0.0, -1.0),   0.5, material_right));
  // render data
  RenderData render_data {};
  render_data.m_camera = &camera;
  render_data.m_samples_per_pixel = args.m_samples;
  render_data.m_world = &world;
  // render
  std::cout << "Begin rendering at " << file_data.m_width << 'x' << file_data.m_height
            << '@' << render_data.m_samples_per_pixel << "spp.\n";
  keteRay(render_data, file_data);
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
