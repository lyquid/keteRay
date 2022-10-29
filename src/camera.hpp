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

#include "ray.hpp"

namespace ktp {

class Camera {
 public:

  Camera(): Camera(90.0, 16.0 / 9.0) {}

  /**
   * @brief Constructs a new Camera object.
   * @param vfov Vertical field of view in degrees.
   * @param aspect_ratio The aspect ratio. V/H.
   */
  Camera(double vfov, double aspect_ratio):
    Camera(
      Point(0.0, 0.0, 0.0),  // look_from
      Point(0.0, 0.0, -1.0), // look_at
      Vector(0.0, 1.0, 0.0), // vup
      vfov,
      aspect_ratio
    ) {}

  Camera(
    Point look_from,
    Point look_at,
    Vector vup,
    double focus_dist,
    double vfov = 90.0,
    double aspect_ratio = 16.0 / 9.0,
    double aperture = 0.0
  );

  /**
   * @brief Use this to know the actual aspect ratio of the camera.
   * @return The aspect ratio currently in use.
   */
  auto aspectRatio() const { return m_aspect_ratio; }

  Ray getRay(double s, double t) const {
    const Vector rd {m_lens_radius * randomInUnitDisk()};
    const Vector offset {m_u * rd.x + m_v * rd.y};
    return Ray(m_origin + offset, m_lower_left_corner + s * m_horizontal + t * m_vertical - m_origin - offset);
  }

 private:

  double m_aspect_ratio {};
  Point  m_lower_left_corner {};
  Point  m_origin {};
  Vector m_horizontal {};
  Vector m_vertical {};
  Vector m_u {}, m_v {}, m_w {};
  double m_lens_radius {};
};

}

#endif
