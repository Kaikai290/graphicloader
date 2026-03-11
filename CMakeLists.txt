cmake_minimum_required(VERSION 3.30)
project(graphicloader VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/vendor/stb)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/vendor/glad/include)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends)

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

  vendor/imgui/imgui.cpp
  vendor/imgui/imgui_demo.cpp
  vendor/imgui/imgui_draw.cpp
  vendor/imgui/imgui_tables.cpp
  vendor/imgui/imgui_widgets.cpp

  vendor/imgui/backends/imgui_impl_glfw.cpp
  vendor/imgui/backends/imgui_impl_opengl3.cpp
)
IF(BASEEXAMPLE)
ADD_DEFINITIONS(-DBASEEXAMPLE=ON)
add_executable(BaseLayer
  example/src/main.cpp
  example/src/baselayer.h
  example/src/imguiexample.h
)
  target_link_libraries(graphicloader PUBLIC glad glfw opengl32 glm)
  target_link_libraries(BaseLayer PUBLIC graphicloader) 
ENDIF(BASEEXAMPLE)

IF(GRASSEXAMPLE)
ADD_DEFINITIONS(-DGRASSEXAMPLE=ON)
  add_executable(GrassLayer
  example/src/main.cpp
  example/src/grasslayer.h
  example/src/imguiexample.h
)
  target_link_libraries(graphicloader PUBLIC glad glfw opengl32 glm)
  target_link_libraries(GrassLayer PUBLIC graphicloader) 
ENDIF(GRASSEXAMPLE)

