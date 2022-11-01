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

#ifndef KTP_GUI_HPP_
#define KTP_GUI_HPP_

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


} } // namespace gui/ktp

#endif
