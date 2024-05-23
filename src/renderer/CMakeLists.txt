add_library(keteRayRenderer
  camera.cpp
  keteray.cpp
  random.cpp
)

if(DEFINED CMAKE_TOOLCHAIN_FILE)
target_link_libraries(keteRayRenderer PRIVATE
  glm::glm
)
else()
target_link_libraries(keteRayRenderer PRIVATE
  glm
)
endif()
