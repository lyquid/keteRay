add_executable(keteray
  main.cpp
)

add_library(libKeteray
  camera.cpp
  config.cpp
  hittable.cpp
  keteray.cpp
  material.cpp
  scene.cpp
  sphere.cpp
)

add_library(guiKeteray
  gui.cpp
)

configure_file(../config/config.json ./ COPYONLY)

target_compile_features(keteray PUBLIC cxx_std_17)
set_target_properties(keteray PROPERTIES CXX_EXTENSIONS OFF)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	set(MY_DEBUG_OPTIONS /Wall /RTC)
	set(MY_RELEASE_OPTIONS /w3 /O2)
	target_compile_options(keteray PUBLIC "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
	target_compile_options(keteray PUBLIC "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	set(MY_DEBUG_OPTIONS -Wall -Wconversion -Wdouble-promotion -Weffc++ -Wextra -Wfloat-equal -Wmain -Wshadow -fstack-usage -pedantic -g3)
	set(MY_RELEASE_OPTIONS -O2)
	target_compile_options(keteray PUBLIC "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
	target_compile_options(keteray PUBLIC "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(MY_DEBUG_OPTIONS -Wall -Wconversion -Wdouble-promotion -Weffc++ -Wextra -Wfloat-equal -Wmain -Wshadow -pedantic -g3)
	set(MY_RELEASE_OPTIONS -O2)
	target_compile_options(keteray PUBLIC "$<$<CONFIG:DEBUG>:${MY_DEBUG_OPTIONS}>")
	target_compile_options(keteray PUBLIC "$<$<CONFIG:RELEASE>:${MY_RELEASE_OPTIONS}>")
endif()

if(DEFINED CMAKE_TOOLCHAIN_FILE)
  target_link_libraries(libKeteray
    glm::glm
    nlohmann_json::nlohmann_json
  )
  target_link_libraries(guiKeteray PRIVATE
    imgui::imgui
    ImGui-SFML::ImGui-SFML
    sfml-system
    sfml-graphics
    sfml-window
  )
  target_link_libraries(keteray PRIVATE
    libKeteray
    guiKeteray
  )
else() # no vcpkg
  target_include_directories(guiKeteray PRIVATE ${keteRay_SOURCE_DIR}/lib/imgui-1.88)
  target_include_directories(guiKeteray PRIVATE ${keteRay_SOURCE_DIR}/lib/imgui-sfml)
  target_link_libraries(libKeteray
    glm
    nlohmann_json::nlohmann_json
  )
  target_link_libraries(guiKeteray PRIVATE
    imgui
    imgui-sfml
    sfml-system
    sfml-graphics
    sfml-window
  )
  target_link_libraries(keteray PRIVATE
    libKeteray
    guiKeteray
  )
endif()

install(TARGETS keteray RUNTIME DESTINATION ${BIN_DIR})
