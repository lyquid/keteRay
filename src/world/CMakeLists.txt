add_library(keteRayWorld
  hittable.cpp
  material.cpp
  rectangle.cpp
  scene.cpp
  sphere.cpp
  texture.cpp
)

target_include_directories(keteRayWorld PRIVATE ${Stb_INCLUDE_DIR})

if(DEFINED CMAKE_TOOLCHAIN_FILE)
  target_link_libraries(keteRayWorld PRIVATE
    glm::glm
  )
else()
  target_link_libraries(keteRayWorld PRIVATE
    glm
  )
endif()
