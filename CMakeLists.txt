cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")

project(graphicloader VERSION 0.1 LANGUAGES C CXX)

find_package(OpenGL REQUIRED) 

add_subdirectory(vendor/glfw) 

add_executable(app src/main.cpp src/application.cpp src/application.h src/window.cpp src/window.h) 

target_include_directories(app PUBLIC glfw)

if (WIN32)
  target_link_libraries(app glfw opengl32})
endif(WIN32)

if (UNIX)
  target_link_libraries(app glfw GL)
endif (UNIX)


