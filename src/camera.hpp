/**
 * @file camera.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief Camera class.
 * @version 0.1
 * @date 2022-10-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KTP_CAMERA_HPP_
#define KTP_CAMERA_HPP_

#include "owert.hpp"
#include "ray.hpp"

namespace ktp {

class Camera {
 public:
 auto aspectRatio() const { return aspect_ratio; }
  Ray getRay(double u, double v) const {
    return Ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
  }
 private:
  double aspect_ratio {16.0 / 9.0};
  double viewport_height {2.0};
  double viewport_width {aspect_ratio * viewport_height};
  double focal_length {1.0};
  Point origin {0.0, 0.0, 0.0};
  Vector horizontal {viewport_width, 0.0, 0.0};
  Vector vertical {0.0, viewport_height, 0.0};
  Point lower_left_corner {origin - horizontal / 2.0 - vertical / 2.0 - Vector(0.0, 0.0, focal_length)};
};

}

#endif
