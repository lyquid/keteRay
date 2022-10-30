#include "gui.hpp"
#include "keteray.hpp"
#include "libppm.hpp"
#include <imgui.h>
#include <imgui-SFML.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

ppm::PPMFileData* ktp::gui::file_data {nullptr};
ktp::RenderData*  ktp::gui::render_data {nullptr};

void ktp::gui::renderingThread(sf::RenderWindow* window) {
  // activate the window's context
  window->setActive(true);
  // the rendering loop
  while (window->isOpen()) {
    window->clear(sf::Color::Black);
    // draw...
    // end the current frame
    window->display();
  }
}

void ktp::gui::start(RenderData* render_data_in, ppm::PPMFileData* file_data_in) {
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

    window.clear();
    ImGui::SFML::Render(window);
    // end the current frame
    window.display();
  }
  ImGui::SFML::Shutdown();
}
