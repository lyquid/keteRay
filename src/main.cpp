#include "libppm.hpp"
#include "ray.hpp"

ppm::Color ray_color(const ktp::Ray& ray) {
  const auto unit_direction {ray.normalizeDirection()};
  auto t {0.5 * (unit_direction.y + 1.0)};
  return (1.0 - t) * ppm::Color(1.0, 1.0, 1.0) + t * ppm::Color(0.5, 0.7, 1.0);
}

int main(int argc, char* argv[]) {
  constexpr auto aspect_ratio {16.0 / 9.0};
  // camera
  constexpr auto viewport_height {2.0};
  constexpr auto viewport_width {aspect_ratio * viewport_height};
  constexpr auto focal_length {1.0};
  constexpr auto origin {ktp::Point{0, 0, 0}};
  constexpr auto horizontal {ktp::Vector{viewport_width, 0, 0}};
  constexpr auto vertical {ktp::Vector{0, viewport_height, 0}};
  constexpr auto lower_left_corner {origin - horizontal / 2.0 - vertical / 2.0 - ktp::Vector(0, 0, focal_length)};
  // image data
  ppm::PPMFileData data {};
  data.m_name = "render.ppm";
  data.m_width  = 2048;
  data.m_height = static_cast<int>(data.m_width / aspect_ratio);
  data.m_pixels.reserve(data.m_width * data.m_height);
  // pixels
  // ppm::generateTestImage(data);
  for (int j = data.m_height - 1; j >= 0; --j) {
    std::cout << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < data.m_width; ++i) {
      const auto u {static_cast<double>(i) / (data.m_width  - 1)};
      const auto v {static_cast<double>(j) / (data.m_height - 1)};
      const ktp::Ray ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
      data.m_pixels.push_back(ray_color(ray));
    }
  }
  // file generation
  ppm::makePPMFile(data);

  return 0;
}
