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

namespace ktp {

struct CameraConfig;
struct ImageData;
struct RenderData;

namespace gui {

extern CameraConfig* camera_data;
extern ImageData*    file_data;
extern RenderData*   render_data;

void start(RenderData* render_data_in, CameraConfig* camera_in, ImageData* file_data_in);

bool layout();
void cameraSection(bool rendering);
void fileSection(bool rendering);
void renderSection(bool rendering);
void sceneSection(bool rendering);

} } // namespace gui/ktp

#endif
