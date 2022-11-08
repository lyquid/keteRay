add_library(keteRayWorld
  hittable.cpp
  material.cpp
  rectangle.cpp
  scene.cpp
  sphere.cpp
  texture.cpp
)

if(DEFINED CMAKE_TOOLCHAIN_FILE)
  target_link_libraries(keteRayWorld PRIVATE
    glm::glm
  )
else()
  target_link_libraries(keteRayWorld PRIVATE
    glm
  )
endif()
