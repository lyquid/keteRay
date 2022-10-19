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

struct Color {
  Color(int red, int green, int blue): r {red}, g {green}, b {blue} {}
  int r{}, g{}, b{};
};

using Pixels = std::vector<Color>;

struct PPMFileData {
  const int   m_channels_per_color {3};
  int         m_height {};
  std::string m_name {};
  Pixels      m_pixels {};
  int         m_width {};
};

void makePPMFile(const PPMFileData& data) {
  std::ofstream image_file {data.m_name};
  // header for ppm file
  image_file << "P3\n" << data.m_width << ' ' << data.m_height << "\n255\n";
  // write pixels to file. 1 RGB triplet per row
  for (auto i = 0u; i < data.m_pixels.size(); ++i) {
    image_file << data.m_pixels[i].r << ' ';
    image_file << data.m_pixels[i].g << ' ';
    image_file << data.m_pixels[i].b << '\n';
  }
  image_file.close();
}

} // namespace libppm

#endif // LIBPPM_HPP_
