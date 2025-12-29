#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "application.h"
#include "window.h"

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods);

void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

void windowSizeCallback(GLFWwindow *window, int width, int height);

Window::Window() {}

Window::~Window() { glfwDestroyWindow(window); }

void Window::init(const ApplicationSpec spec) {
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  glfwWindowHint(GLFW_RESIZABLE, spec.resizable);
  glfwWindowHint(GLFW_FOCUSED, spec.windowFocused);
  glfwWindowHint(GLFW_CENTER_CURSOR, spec.centerCusor);
  //glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);

  window =
      glfwCreateWindow(spec.width, spec.height, spec.title.c_str(), NULL, NULL);
  if (!window) {
    glfwTerminate();
    std::cout << "Failed to initalize Window" << std::endl;
  }
  glfwMakeContextCurrent(window);
  
  if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
    std::cout << "no" << std::endl;

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

  lastTime = glfwGetTime();
}

void Window::update() {
  glClear(GL_COLOR_BUFFER_BIT);

  glfwSwapBuffers(window);

  glfwPollEvents();

  double currentTime = glfwGetTime();
  deltaTime = currentTime - lastTime;
  lastTime = currentTime;
}

bool Window::shouldClose() { return !glfwWindowShouldClose(window); }

const GLFWwindow *Window::getWindow() const { return window; }

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
  Application::getApplication().getKeys().updateState(key, action);
}

void cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {}

void windowSizeCallback(GLFWwindow *window, int width, int height) {
  glfwGetWindowSize(window, &width, &height);
}
