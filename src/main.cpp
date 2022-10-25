#include "camera.hpp"
#include "hittable.hpp"
#include "owert.hpp"
#include "ray.hpp"
#include "sphere.hpp"

int main(int argc, char* argv[]) {
  const ktp::Camera camera {};
  // image data
  ppm::PPMFileData data {};
  data.m_name = "render.ppm";
  data.m_width  = 2048;
  data.m_height = static_cast<int>(data.m_width / camera.aspectRatio());
  data.m_pixels.reserve(data.m_width * data.m_height);
  // world
  ktp::HittableList world {};
  world.add(std::make_shared<ktp::Sphere>(ktp::Point(0.0,    0.0, -1.0),   0.5));
  world.add(std::make_shared<ktp::Sphere>(ktp::Point(0.0, -100.5, -1.0), 100.0));
  // pixels
  for (int j = data.m_height - 1; j >= 0; --j) {
    std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < data.m_width; ++i) {
      const auto u {static_cast<double>(i) / (data.m_width  - 1.0)};
      const auto v {static_cast<double>(j) / (data.m_height - 1.0)};
      const ktp::Ray ray {camera.getRay(u, v)};
      data.m_pixels.push_back(ktp::colorToPPM(ray.rayColor(world)));
    }
  }
  // file generation
  ppm::makePPMFile(data);

  return 0;
}
