cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")

project(graphicloader VERSION 0.1 LANGUAGES C CXX)

find_package(OpenGL REQUIRED) 

include_directories( ${CMAKE_SOURCE_DIR}/vendor/glad/include)

add_library(glad STATIC ${CMAKE_SOURCE_DIR}/vendor/glad/glad.c)
add_subdirectory(vendor/glfw) 

add_executable(app 
  src/main.cpp 
  src/application.cpp 
  src/application.h 
  src/window.cpp 
  src/window.h
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
) 

target_include_directories(app PUBLIC glfw glad)

if (WIN32)
  target_link_libraries(app glad glfw opengl32)
endif(WIN32)

if (UNIX)
  target_link_libraries(app glad glfw GL)
endif (UNIX)


