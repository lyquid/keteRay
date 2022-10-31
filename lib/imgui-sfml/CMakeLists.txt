add_library(imgui-sfml
  imgui-SFML.cpp
  # ../imgui-1.88/imgui_impl_opengl3.cpp
)

target_include_directories(imgui-sfml PRIVATE ${keteRay_SOURCE_DIR}/lib/imgui-1.88)

target_link_libraries(imgui-sfml PRIVATE
  imgui
  # OpenGL
  # GLEW
)
