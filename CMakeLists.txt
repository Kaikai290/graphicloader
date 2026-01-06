cmake_minimum_required(VERSION 3.30)
project(graphicloader VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_library(glad STATIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/glad.c)

add_subdirectory(
  "./vendor/glfw/"
)

add_subdirectory(
  "./vendor/glm/"
)
add_library(graphicloader 
  src/application.cpp 
  src/application.h 
  src/window.cpp 
  src/window.h
  src/log.cpp
  src/log.h
  src/camera.cpp
  src/camera.h
  src/key.cpp
  src/key.h

  src/renderer/shader_manager.cpp
  src/renderer/shader_manager.h
  src/renderer/vao.cpp
  src/renderer/vao.h
  src/renderer/vbo.cpp
  src/renderer/vbo.h
  src/renderer/ibo.cpp
  src/renderer/ibo.h
  src/renderer/texture_manager.cpp
  src/renderer/texture_manager.h
)

add_executable(Example
  example/src/main.cpp
  example/src/examplelayer.h
)

if (WIN32)
  target_link_libraries(graphicloader PUBLIC glad glfw opengl32 glm)
  target_link_libraries(Example PUBLIC graphicloader) 
endif(WIN32)
