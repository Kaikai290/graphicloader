#include "event.h"

#include <iostream>
#include <memory>

#include "window.h"
#include "application.h"

namespace LZ {

static double lastX;
static double lastY;

static bool firstMove = true;

void errorCallback(int code, const char *description) {
  std::cout << description << std::endl;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods) {
  Window* eventWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
  std::shared_ptr<KeyEvent> keyEvent = std::make_shared<KeyEvent>(eventWindow, key, action);
  Application::getApplication().pushEvent((keyEvent));


  Application::getApplication().getInputs().updateState(key, action);
}

void cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
  Window* eventWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
  std::shared_ptr<MouseMoveEvent> mouseMoveEvent = std::make_shared<MouseMoveEvent>(eventWindow, xpos, ypos);
  Application::getApplication().pushEvent((mouseMoveEvent));
  if (firstMove) {
    firstMove = false;
    lastX = xpos;
    lastY = ypos;
  }
  double xoffset = xpos - lastX;
  double yoffset = lastY - ypos;
  Application::getApplication().updateMouse(xpos, ypos, lastX, lastY);
  lastX = xpos;
  lastY = ypos;

  float sensitivity = 0.1f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  LazyCamera &cam = Application::getApplication().getMainCamera();
  float &yaw = cam.getYaw();
  float &pitch = cam.getPitch();

  yaw += xoffset;
  pitch += yoffset;

  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;

  cam.update();
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
  Window* eventWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
  std::shared_ptr<MouseButtonEvent> mouseButtonEvent = std::make_shared<MouseButtonEvent>(eventWindow, button, action);
  Application::getApplication().pushEvent((mouseButtonEvent));
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {}

void windowSizeCallback(GLFWwindow *window, int width, int height) {
  ScreenDim &screen = Application::getApplication().getDimensions();
  screen.width = width;
  screen.height = height;
  glViewport(0, 0, screen.width, screen.height);
}
}
