#include "libppm.hpp"
#include <glm/vec3.hpp>

int main(int argc, char* argv[]) {
  // image data
  libppm::PPMFileData data {};
  data.m_name = "render.ppm";
  data.m_height = 1024;
  data.m_width  = 1024;
  data.m_pixels.reserve(data.m_width * data.m_height);

  // pixels
  for (auto row = data.m_height - 1; row >= 0; --row) {
    std::cout << "\rScanlines remaining: " << row << ' ' << std::flush;
    for (auto col = 0; col < data.m_width; ++col) {
      constexpr auto magic_num {255.999};
      const libppm::Color i_color {
        static_cast<int>(magic_num * static_cast<double>(col) / (data.m_width  - 1)),
        static_cast<int>(magic_num * static_cast<double>(row) / (data.m_height - 1)),
        static_cast<int>(magic_num * 0.25)
      };
      data.m_pixels.push_back(i_color);
    }
  }
  std::cout << "\rScanlines processing finished.\n";

  // file generation
  std::cout << "Generating ppm file...";
  libppm::makePPMFile(data);
  std::cout << "\rRender generated successfully!";

  return 0;
}
