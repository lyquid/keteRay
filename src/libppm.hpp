/**
 * @file libppm.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief A library for creating portable pixmap format (PPM) image files.
 * @version 0.1
 * @date 2022-10-18
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef LIBPPM_HPP_
#define LIBPPM_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace libppm {

// **** forward declarations ****
struct Color;
using Pixels = std::vector<Color>;
void writePixel(std::ostream& file, const Color& color);
// **** forward declarations ****

/**
 * @brief A RGB color [0, 1].
 */
struct Color {
  Color(double red, double green, double blue): r(red), g(green), b(blue) {}
  double r{}, g{}, b{};
};

/**
 * @brief Struct containing the info needed to generate a ppm file.
 */
struct PPMFileData {
  const int   m_channels_per_color {3};
  int         m_height {};
  std::string m_name {};
  Pixels      m_pixels {};
  int         m_width {};
};

/**
 * @brief Generates a test image to see if everything is working.
 * @param data The info of the file to be generated.
 */
void generateTestImage(PPMFileData& data) {
  for (auto row = data.m_height - 1; row >= 0; --row) {
    std::cout << "\rScanlines remaining: " << row << ' ' << std::flush;
    for (auto col = 0; col < data.m_width; ++col) {
      const Color color {
        static_cast<double>(col) / (data.m_width  - 1),
        static_cast<double>(row) / (data.m_height - 1),
        0.25
      };
      data.m_pixels.push_back(color);
    }
  }
  std::cout << "\rScanlines processing finished.\n";
}

/**
 * @brief Generates a ppm file.
 * @param data The data of the ppm file.
 */
void makePPMFile(const PPMFileData& data) {
  std::ofstream image_file {data.m_name};
  // header for ppm file
  image_file << "P3\n" << data.m_width << ' ' << data.m_height << "\n255\n";
  // write pixels to file. 1 RGB triplet per row
  for (auto i = 0u; i < data.m_pixels.size(); ++i) {
    writePixel(image_file, data.m_pixels[i]);
  }
  image_file.close();
}

/**
 * @brief Writes a pixel (rgb [0, 255] triplet) to the given stream.
 * @param out The output stream. Recommended to be a file.
 * @param color A color in rgb [0, 1] format.
 */
inline void writePixel(std::ostream& out, const Color& color) {
  constexpr auto magic_num {255.999};
  out << static_cast<int>(magic_num * color.r) << ' '
      << static_cast<int>(magic_num * color.g) << ' '
      << static_cast<int>(magic_num * color.b) << '\n';
}

} // namespace libppm

#endif // LIBPPM_HPP_
