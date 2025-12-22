#include "window.h"

#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

Window::Window() {
  if (glfwInit())
    std::cout << "Initalize GLFW" << std::endl;
}

Window::~Window() {
  glfwTerminate();
}

void Window::init(const WindowSpec spec) {
  window = glfwCreateWindow(spec.width, spec.height, spec.title.c_str(), NULL, NULL);
  if (!window) {
    glfwTerminate();
    std::cout << "Failed to initalize Window" << std::endl;
  }
  glfwMakeContextCurrent(window);

}

void Window::update() {
  glClear(GL_COLOR_BUFFER_BIT);
  glfwSwapBuffers(window);
  glfwPollEvents();
}

bool Window::shouldClose() {
  return !glfwWindowShouldClose(window);
}

const GLFWwindow* Window::getWindow() const {
  return window;
}
