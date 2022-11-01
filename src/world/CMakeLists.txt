add_library(keteRayWorld
  hittable.cpp
  material.cpp
  scene.cpp
  sphere.cpp
)

if(DEFINED CMAKE_TOOLCHAIN_FILE)
target_link_libraries(keteRayWorld PRIVATE
  glm::glm
)
else()
target_link_libraries(keteRayWorld PRIVATE
  # glm::glm
)
endif()
