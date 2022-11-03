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

#ifndef KETERAY_SRC_RENDERER_CAMERA_HPP_
#define KETERAY_SRC_RENDERER_CAMERA_HPP_

#include "renderer_types.hpp"

namespace ktp {

struct CameraConfig {
  double m_aperture {1.0};
  double m_aspect_ratio {16.0 / 9.0};
  double m_focus_dist {0.0};
  Vector m_look_at   {0.0, 0.0, -1.0};
  Vector m_look_from {0.0, 0.0,  0.0};
  Vector m_vertical  {0.0, 1.0,  0.0};
  double m_vfov {90.0};
};

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

  Camera(const CameraConfig& config):
    Camera(
      config.m_look_from,
      config.m_look_at,
      config.m_vertical,
      config.m_focus_dist,
      config.m_vfov,
      config.m_aspect_ratio,
      config.m_aperture
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

  Ray getRay(double s, double t) const;

  void reset(const CameraConfig& config);

 private:

  double m_aspect_ratio {};
  Point  m_lower_left_corner {};
  Point  m_origin {};
  Vector m_horizontal {};
  Vector m_vertical {};
  Vector m_u {}, m_v {}, m_w {};
  double m_lens_radius {};
};

} // namespace ktp

#endif
