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
  libppm::generateTestImage(data);
  // file generation
  libppm::makePPMFile(data);

  return 0;
}
