add_library(keteRayGUI
  gui.cpp
)

if(DEFINED CMAKE_TOOLCHAIN_FILE)
target_link_libraries(keteRayGUI PRIVATE
  imgui::imgui
  ImGui-SFML::ImGui-SFML
  sfml-system
  sfml-graphics
  sfml-window
)
else()
target_link_libraries(keteRayGUI PRIVATE
  imgui
  ImGui-SFML
  sfml-system
  sfml-graphics
  sfml-window
)
endif()
