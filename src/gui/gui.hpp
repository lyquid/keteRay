/**
 * @file gui.hpp
 * @author Alejandro Castillo Blanco (alexcastilloblanco@gmail.com)
 * @brief GUI rendering utilities.
 * @version 0.1
 * @date 2022-10-30
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef KETERAY_SRC_GUI_GUI_HPP_
#define KETERAY_SRC_GUI_GUI_HPP_

namespace ppm { struct PPMFileData; }

namespace ktp {

struct CameraConfig;
struct RenderData;

namespace gui {

extern CameraConfig* camera_data;
extern ppm::PPMFileData* file_data;
extern RenderData* render_data;

void start(RenderData* render_data_in, CameraConfig* camera_in, ppm::PPMFileData* file_data_in);

void layout();
void cameraSection(bool rendering);
void fileSection(bool rendering);
void renderSection(bool rendering);
void sceneSection(bool rendering);

// framerate 
constexpr int32_t k_FPS {60};
// wait time in milliseconds
constexpr int32_t k_WAIT_TIME {1000 / k_FPS};
} } // namespace gui/ktp

#endif
