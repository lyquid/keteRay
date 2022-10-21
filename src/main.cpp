#include "libppm.hpp"
#include "ray.hpp"

int main(int argc, char* argv[]) {
  ktp::Ray ray {};
  // image data
  ppm::PPMFileData data {};
  data.m_name = "render.ppm";
  data.m_height = 1024;
  data.m_width  = 1024;
  data.m_pixels.reserve(data.m_width * data.m_height);
  // pixels
  ppm::generateTestImage(data);
  // file generation
  ppm::makePPMFile(data);

  return 0;
}
