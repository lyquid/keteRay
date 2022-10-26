#include "camera.hpp"
#include "hittable.hpp"
#include "keteray.hpp"
#include "ray.hpp"
#include "sphere.hpp"

int main(int argc, char* argv[]) {
  constexpr auto samples_per_pixel {100};
  // camera
  ktp::Camera camera {};
  // image data
  ppm::PPMFileData file_data {};
  file_data.m_width  = 1024;
  file_data.m_height = static_cast<int>(file_data.m_width / camera.aspectRatio());
  file_data.m_pixels.reserve(file_data.m_width * file_data.m_height);
  file_data.m_name = "render_"
    + std::to_string(file_data.m_width) + "x"
    + std::to_string(file_data.m_height) + "_"
    + std::to_string(samples_per_pixel) + "_samples.ppm";
  // world
  ktp::HittableList world {};
  world.add(std::make_shared<ktp::Sphere>(ktp::Point(0.0,    0.0, -1.0),   0.5));
  world.add(std::make_shared<ktp::Sphere>(ktp::Point(0.0, -100.5, -1.0), 100.0));
  // render data
  ktp::RenderData render_data {};
  render_data.m_camera = &camera;
  render_data.m_samples_per_pixel = samples_per_pixel;
  render_data.m_world = &world;
  // render
  ktp::keteRay(render_data, file_data);
  // file generation
  ppm::makePPMFile(file_data);

  return 0;
}
