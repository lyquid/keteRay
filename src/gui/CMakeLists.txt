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
target_include_directories(keteRayGUI PRIVATE ${keteRay_SOURCE_DIR}/lib/imgui-1.88)
target_include_directories(keteRayGUI PRIVATE ${keteRay_SOURCE_DIR}/lib/imgui-sfml)
target_link_libraries(keteRayGUI PRIVATE
  imgui
  ImGui-SFML
  sfml-system
  sfml-graphics
  sfml-window
)
endif()
