#include "../renderer/camera.hpp"
#include "../gui/gui.hpp"
#include "../world/hittable.hpp"
#include "../renderer/keteray.hpp"
#include "../libppm.hpp"
#include "../world/scene.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <thread>

ktp::CameraConfig* ktp::gui::camera_data {nullptr};
ppm::PPMFileData*  ktp::gui::file_data {nullptr};
ktp::RenderData*   ktp::gui::render_data {nullptr};

void ktp::gui::start(RenderData* render_data_in, CameraConfig* camera_in, ppm::PPMFileData* file_data_in) {
  camera_data = camera_in;
  file_data = file_data_in;
  render_data = render_data_in;

  sf::VideoMode desktop {sf::VideoMode::getDesktopMode()};
  sf::RenderWindow window {sf::VideoMode(1024, 768, desktop.bitsPerPixel), "keteRay"};
  if (!ImGui::SFML::Init(window)) return;

  sf::Clock delta_clock {};
  while (window.isOpen()) {
    sf::Event event {};
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(window, event);
      if (event.type == sf::Event::Closed) window.close();
    }
    ImGui::SFML::Update(window, delta_clock.restart());

    ImGui::ShowDemoWindow();
    layout();

    window.clear();
    ImGui::SFML::Render(window);
    window.display();
  }
  ImGui::SFML::Shutdown();
}

void ktp::gui::layout() {
  ImGui::SetNextWindowSize(ImVec2(510, 528), ImGuiCond_FirstUseEver);

  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      ImGui::MenuItem("Close");
      ImGui::EndMenu();
    }
     ImGui::EndMenuBar();
  }
  static std::string message {};
  static int progress {};
  static bool rendering {false};
  ImGui::BeginDisabled(rendering);
    ImGui::Separator();
    sceneSection(rendering);
    ImGui::Separator();
    fileSection(rendering);
    ImGui::Separator();
    cameraSection(rendering);
    ImGui::Separator();
    renderSection(rendering);
    ImGui::Separator();
    if (ImGui::Button("Render")) {
      rendering = true;
      message = "Begin rendering at " + std::to_string(render_data->m_width) + 'x' + std::to_string(render_data->m_height)
              + '@' + std::to_string(render_data->m_samples_per_pixel) + "spp.\n";
      std::cout << message;
      std::thread render_thread {[] {
        keteRay(*render_data, *file_data, progress);
        progress = 0;
        ppm::makePPMFile(*file_data);
        message = "Rendered at " + std::to_string(render_data->m_width) + 'x' + std::to_string(render_data->m_height)
                + '@' + std::to_string(render_data->m_samples_per_pixel) + "spp.\n" + "PPM file generated successfully!";
        rendering = false;
      }};
      render_thread.detach();
    }
    ImGui::SameLine();
    if (ImGui::Button("Randomize world")) {
      render_data->m_scene.m_world = render_data->m_scene.m_function();
    }
  ImGui::EndDisabled();
  ImGui::Separator();
  ImGui::Separator();
  ImGui::Text(message.c_str());
  if (rendering) {
    if (progress != 0)
      ImGui::Text(("Scanlines remaining: " + std::to_string(progress)).c_str());
    else
      ImGui::Text("Generating ppm file...");
  }
}

void ktp::gui::sceneSection(bool rendering) {
  ImGui::Text("Scene");
  ImGui::BeginDisabled(rendering);
    static ImGuiComboFlags flags {};
    // here we store our selection data as an index.
    static auto current_item {scenes.find(k_DEFAULT_SCENE)->first};
    // pass in the preview value visible before opening the combo (it could be anything)
    const char* combo_preview {scenes.find(current_item)->first.c_str()};
    if (ImGui::BeginCombo("Choose a scene", combo_preview, flags)) {
      for (auto it = scenes.begin(); it != scenes.end(); ++it) {
        const bool is_selected {current_item == it->first};
        if (ImGui::Selectable(it->first.c_str(), is_selected)) current_item = it->first;
        // set the initial focus when opening the combo (scrolling + keyboard navigation focus)
        if (is_selected) ImGui::SetItemDefaultFocus();
      }
      render_data->m_scene = scenes[current_item];
      ImGui::EndCombo();
    }
  ImGui::EndDisabled();
}

void ktp::gui::cameraSection(bool rendering) {
  static double step {0.01};
  ImGui::Text("Camera");
  // aperture
  ImGui::BeginDisabled(rendering);
  if (ImGui::InputScalar("Aperture", ImGuiDataType_Double, &camera_data->m_aperture, &step, &step, "%.3f")) {
    render_data->m_camera->reset(*camera_data);
  }
  // aspect ratio
  static bool aspect_ratio_locked {true};
  ImGui::BeginDisabled(aspect_ratio_locked);
    if (ImGui::InputDouble("Aspect ratio", &camera_data->m_aspect_ratio)) {
      render_data->m_camera->reset(*camera_data);
    }
    ImGui::SameLine();
    ImGui::Checkbox("Locked", &aspect_ratio_locked);
  ImGui::EndDisabled();
  // focus distance
  if (ImGui::InputScalar("Focus distance", ImGuiDataType_Double, &camera_data->m_focus_dist, &step, &step, "%.3f")) {
    render_data->m_camera->reset(*camera_data);
  }
  // look from
  static float look_from[3] {(float)camera_data->m_look_from.x, (float)camera_data->m_look_from.y, (float)camera_data->m_look_from.z};
  if (ImGui::InputFloat3("Look from", look_from, "%.2f")) {
    camera_data->m_look_from = Vector(look_from[0], look_from[1], look_from[2]);
    render_data->m_camera->reset(*camera_data);
  }
  // look at
  static float look_at[3] {(float)camera_data->m_look_at.x, (float)camera_data->m_look_at.y, (float)camera_data->m_look_at.z};
  if (ImGui::InputFloat3("Look at", look_at, "%.2f")) {
    camera_data->m_look_at = Vector(look_at[0], look_at[1], look_at[2]);
    render_data->m_camera->reset(*camera_data);
  }
  // vertical
  static float vertical[3] {(float)camera_data->m_vertical.x, (float)camera_data->m_vertical.y, (float)camera_data->m_vertical.z};
  if (ImGui::InputFloat3("Vertical", vertical, "%.2f")) {
    camera_data->m_vertical = Vector(vertical[0], vertical[1], vertical[2]);
    render_data->m_camera->reset(*camera_data);
  }
  // vfov
  static double vfov_step {0.1};
  if (ImGui::InputScalar("Vertical FoV", ImGuiDataType_Double, &camera_data->m_vfov, &vfov_step, &vfov_step, "%.2f")) {
    render_data->m_camera->reset(*camera_data);
  }
  ImGui::EndDisabled();
}

void ktp::gui::fileSection(bool rendering) {
  ImGui::Text("Image file");
  ImGui::BeginDisabled(true);
    ImGui::InputText("File name", &file_data->m_file_name);
  ImGui::EndDisabled();
}

void ktp::gui::renderSection(bool rendering) {
  ImGui::Text("Render");
  ImGui::BeginDisabled(rendering);
  if (ImGui::InputInt("Width", &render_data->m_width)) {
    render_data->m_height = static_cast<int>(render_data->m_width / render_data->m_camera->aspectRatio());
    file_data->m_file_name = createFileName(*render_data, *file_data);
  }
  ImGui::BeginDisabled(true);
    if (ImGui::InputInt("Height", &render_data->m_height)) {
      file_data->m_file_name = createFileName(*render_data, *file_data);
    }
  ImGui::EndDisabled();
  if (ImGui::InputInt("Samples per pixel", &render_data->m_samples_per_pixel)) {
    file_data->m_file_name = createFileName(*render_data, *file_data);
  }
  ImGui::EndDisabled();
}
