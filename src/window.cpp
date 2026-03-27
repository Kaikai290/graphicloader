#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <iostream>

#include "application.h"
#include "window.h"
#include "event.h"

#include "log.h"

namespace LZ {


Window::Window() {}

Window::~Window() {}

void Window::init(const ApplicationSpec spec) {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_RESIZABLE, spec.resizable);
  glfwWindowHint(GLFW_FOCUSED, spec.windowFocused);
  glfwWindowHint(GLFW_CENTER_CURSOR, spec.centerCusor);
  glfwWindowHint(GLFW_SAMPLES, spec.samples);
  // glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);

  window = glfwCreateWindow(spec.dimensions.width, spec.dimensions.height,
                            spec.title.c_str(), NULL, NULL);
  if (!window) {
    glfwTerminate();
    std::cout << "Failed to initalize Window" << std::endl;
  }
  glfwMakeContextCurrent(window);

  GLFW_REFRESH_RATE;

  glfwSetWindowUserPointer(window, this);

  glfwSetKeyCallback(window, keyCallback);

  glfwSetWindowSizeCallback(window, windowSizeCallback);

  if (spec.mouseLock == true)
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  if (spec.rawMouseMoition == true && glfwRawMouseMotionSupported())
    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);

  glfwSetCursorPosCallback(window, cursorPosCallback);

  glfwSetMouseButtonCallback(window, mouseButtonCallback);

  glfwSetScrollCallback(window, scrollCallback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    std::cout << "no" << std::endl;

  glfwSwapInterval(1);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |=
      ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(
      window, true); // Second param install_callback=true will install
                     // GLFW callbacks and chain to existing ones.
  ImGui_ImplOpenGL3_Init();
}

void Window::shutdown() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext(); // should check to see if imgui is init before
                           // shutting down?

  if (window) {
    Log::printInfo("Window Deleted");
    glfwDestroyWindow(window);
  }
}

void Window::pollEvents() { glfwPollEvents(); }

void Window::update() { glfwSwapBuffers(window); }

void Window::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

bool Window::shouldClose() { return !glfwWindowShouldClose(window); }

const GLFWwindow *Window::getWindow() const { return window; }

} // namespace LZ
