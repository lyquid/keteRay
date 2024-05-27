cmake_minimum_required(VERSION 3.12)

if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

project(
  keteRay
  VERSION 0.1.0
  DESCRIPTION "One weekend ray tracer by ketepincho."
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Support folders in IDEs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Macro to ensure a directory exists
macro(ensure_directory_exists dir)
  if(NOT EXISTS ${dir})
    file(MAKE_DIRECTORY ${dir})
  endif()
endmacro()

# Macro to copy files
macro(copy_files src dst)
  file(COPY ${src} DESTINATION ${dst})
endmacro()

# Only if this is the main project
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
  enable_testing()

  # Documentation can be added here
  # find_package(Doxygen)
  # if(Doxygen_FOUND)
  #   add_subdirectory(docs)
  # else()
  #   message(STATUS "Doxygen not found, not building docs")
  # endif()
endif()

# Vcpkg toolchain file and package finding
if(DEFINED CMAKE_TOOLCHAIN_FILE)
  message(STATUS "Using vcpkg toolchain file")
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  find_package(glm CONFIG REQUIRED)
  if(NOT glm_FOUND)
    message(FATAL_ERROR "GLM not found")
  endif()

  find_package(imgui CONFIG REQUIRED)
  if(NOT imgui_FOUND)
    message(FATAL_ERROR "imgui not found")
  endif()

  find_package(ImGui-SFML REQUIRED)
  if(NOT ImGui-SFML_FOUND)
    message(FATAL_ERROR "ImGui-SFML not found")
  endif()

  find_package(nlohmann_json CONFIG REQUIRED)
  if(NOT nlohmann_json_FOUND)
    message(FATAL_ERROR "nlohmann_json not found")
  endif()

  find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
  if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found")
  endif()

  find_package(Stb REQUIRED)
  if(NOT Stb_FOUND)
    message(FATAL_ERROR "Stb not found")
  endif()
else()
  message(STATUS "Using CMake find modules")

  find_package(glm REQUIRED)
  if(NOT glm_FOUND)
    message(FATAL_ERROR "GLM not found")
  endif()

  find_package(nlohmann_json CONFIG REQUIRED)
  if(NOT nlohmann_json_FOUND)
    message(FATAL_ERROR "nlohmann_json not found")
  endif()

  find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
  if(NOT SFML_FOUND)
    message(FATAL_ERROR "SFML not found")
  endif()
endif()

add_subdirectory(src)
add_subdirectory(src/gui)
add_subdirectory(src/renderer)
add_subdirectory(src/world)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Ensure the resources directory exists
ensure_directory_exists("${CMAKE_BINARY_DIR}/src/debug")
ensure_directory_exists("${CMAKE_BINARY_DIR}/src/debug/resources")
ensure_directory_exists("${CMAKE_BINARY_DIR}/src/Release")
ensure_directory_exists("${CMAKE_BINARY_DIR}/src/Release/resources")

# Configure and copy files
configure_file(${CMAKE_SOURCE_DIR}/config/config.json ${CMAKE_BINARY_DIR}/src/debug/config.json COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/config/config.json ${CMAKE_BINARY_DIR}/src/Release/config.json COPYONLY)
copy_files(${CMAKE_SOURCE_DIR}/resources/ ${CMAKE_BINARY_DIR}/src/debug/resources)
copy_files(${CMAKE_SOURCE_DIR}/resources/ ${CMAKE_BINARY_DIR}/src/Release/resources)
