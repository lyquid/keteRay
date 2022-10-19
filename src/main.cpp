#include "libppm.hpp"
#include <glm/vec3.hpp>

int main(int argc, char* argv[]) {
  // image data
  libppm::PPMFileData data {};
  data.m_name = "render.ppm";
  data.m_height = 1024;
  data.m_width  = 1024;
  data.m_pixels.reserve(data.m_width * data.m_height * data.m_channels_per_color);

  // pixels
  for (auto row = data.m_height - 1; row >= 0; --row) {
    std::cout << "\rScanlines remaining: " << row << ' ' << std::flush;
    for (auto col = 0; col < data.m_width; ++col) {
      const     double r {static_cast<double>(col) / (data.m_width  - 1)};
      const     double g {static_cast<double>(row) / (data.m_height - 1)};
      constexpr double b {0.25};

      constexpr auto magic_num {255.999};
      const int ir {static_cast<int>(magic_num * r)};
      const int ig {static_cast<int>(magic_num * g)};
      const int ib {static_cast<int>(magic_num * b)};

      data.m_pixels.push_back(ir);
      data.m_pixels.push_back(ig);
      data.m_pixels.push_back(ib);
    }
  }
  std::cout << "\rScanlines processing finished.\n";

  // file generation
  std::cout << "Generating ppm file...";
  libppm::makePPMFile(data);
  std::cout << "\rRender generated successfully!";

  return 0;
}
