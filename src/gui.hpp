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
namespace sf  { class RenderWindow; }

namespace ktp {

struct RenderData;

namespace gui {

extern ppm::PPMFileData* file_data;
extern RenderData* render_data;

void renderingThread(sf::RenderWindow* window);
void start(RenderData* render_data_in, ppm::PPMFileData* file_data_in);

} } // namespace gui/ktp

#endif
