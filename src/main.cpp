#include "camera.hpp"
#include "hittable.hpp"
#include "keteray.hpp"
#include "ray.hpp"
#include "sphere.hpp"

int main(int argc, char* argv[]) {
  const ktp::Camera camera {};
  // render data
  constexpr auto max_depth {50};
  constexpr auto samples_per_pixel {100};
  // image data
  ppm::PPMFileData data {};
  // data.m_name = "render.ppm";
  data.m_width  = 1024;
  data.m_height = static_cast<int>(data.m_width / camera.aspectRatio());
  data.m_pixels.reserve(data.m_width * data.m_height);
  data.m_name =
    "render_"
    + std::to_string(data.m_width) + "x"
    + std::to_string(data.m_height) + "_"
    + std::to_string(samples_per_pixel) + "_samples.ppm";
  // world
  ktp::HittableList world {};
  world.add(std::make_shared<ktp::Sphere>(ktp::Point(0.0,    0.0, -1.0),   0.5));
  world.add(std::make_shared<ktp::Sphere>(ktp::Point(0.0, -100.5, -1.0), 100.0));
  // pixels
  for (int j = data.m_height - 1; j >= 0; --j) {
    std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < data.m_width; ++i) {
      ktp::Color pixel_color {};
      if (samples_per_pixel <= 1) {
        // no multisampling
        const auto u {static_cast<double>(i) / (data.m_width  - 1)};
        const auto v {static_cast<double>(j) / (data.m_height - 1)};
        const ktp::Ray ray {camera.getRay(u, v)};
        pixel_color = rayColor(ray, world, max_depth);
      } else {
        // multisampling
        for (int s = 0; s < samples_per_pixel; ++s) {
          const auto u {(i + ktp::randomDouble()) / (data.m_width  - 1)};
          const auto v {(j + ktp::randomDouble()) / (data.m_height - 1)};
          const ktp::Ray ray {camera.getRay(u, v)};
          pixel_color += rayColor(ray, world, max_depth);
        }
        const auto scale {1.0 / samples_per_pixel};
        pixel_color *= scale;
      }
      // gamma correction
      pixel_color = glm::sqrt(pixel_color);
      // final pixel color to the data
      data.m_pixels.push_back(ktp::colorToPPM(pixel_color));
    }
  }
  // file generation
  ppm::makePPMFile(data);

  return 0;
}
