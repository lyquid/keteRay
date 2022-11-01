#include "../renderer/camera.hpp"
#include "../gui/gui.hpp"
#include "../world/hittable.hpp"
#include "../renderer/keteray.hpp"
#include "../libppm.hpp"
#include "../world/scene.hpp"
#include <imgui.h>
#include <imgui_stdlib.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

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

    // ImGui::ShowDemoWindow();
    layout();

    window.clear();
    ImGui::SFML::Render(window);
    window.display();
  }
  ImGui::SFML::Shutdown();
}

void ktp::gui::layout() {
  ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);

  if (ImGui::BeginMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      ImGui::MenuItem("Close");
      ImGui::EndMenu();
    }
     ImGui::EndMenuBar();
  }

  ImGui::Separator();

    fileSection();

  ImGui::Separator();

    cameraSection();

  ImGui::Separator();

    renderSection();

  ImGui::Separator();

  if (ImGui::Button("Render")) {
    std::cout << "Begin rendering at " << file_data->m_width << 'x' << file_data->m_height
              << '@' << render_data->m_samples_per_pixel << "spp.\n";
    keteRay(*render_data, *file_data);
    ppm::makePPMFile(*file_data);
    file_data->m_pixels.clear();
  }
  ImGui::SameLine();
  if (ImGui::Button("Randomize world")) {
    *render_data->m_world = randomScene();
  }

  ImGui::End();
}

void ktp::gui::cameraSection() {
  ImGui::Text("Camera");
  if (ImGui::InputDouble("Aperture", &camera_data->m_aperture)) {
    render_data->m_camera->reset(*camera_data);
  }
  if (ImGui::InputDouble("Aspect ratio", &camera_data->m_aspect_ratio)) {
    render_data->m_camera->reset(*camera_data);
  }
  if (ImGui::InputDouble("Focus distance", &camera_data->m_focus_dist)) {
    render_data->m_camera->reset(*camera_data);
  }
  // if (ImGui::InputDouble("Look at", &camera_data->m_look_at)) {

  // }
  // if (ImGui::InputDouble("Look from", &camera_data->m_look_from)) {

  // }
  // if (ImGui::InputDouble("Vertical", &camera_data->m_vertical)) {

  // }
  if (ImGui::InputDouble("Vertical FoV (zoom)", &camera_data->m_vfov)) {
    render_data->m_camera->reset(*camera_data);
  }
}

void ktp::gui::fileSection() {
  ImGui::Text("Image file");
  ImGui::InputText("File name", &file_data->m_file_name);
}

void ktp::gui::renderSection() {
  ImGui::Text("Render");
  if (ImGui::InputInt("Width", &render_data->m_width)) {
    file_data->m_file_name = createFileName(*render_data, *file_data);
  }
  if (ImGui::InputInt("Width", &render_data->m_height)) {
    file_data->m_file_name = createFileName(*render_data, *file_data);
  }
  if (ImGui::InputInt("Samples per pixel", &render_data->m_samples_per_pixel)) {
    file_data->m_file_name = createFileName(*render_data, *file_data);
  }
}
