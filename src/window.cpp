#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "application.h"
#include "window.h"
  
static double lastX;
static double lastY;

static bool firstMove = true;

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
  // glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);

  window =
      glfwCreateWindow(spec.dimensions.width, spec.dimensions.height,
                       spec.title.c_str(), NULL, NULL);
  if (!window) {
    glfwTerminate();
    std::cout << "Failed to initalize Window" << std::endl;
  }
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    std::cout << "no" << std::endl;

  glEnable(GL_DEPTH_TEST);  
  glEnable(GL_CULL_FACE);
  //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );


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
  glfwSwapBuffers(window);

  glfwPollEvents();

  double currentTime = glfwGetTime();
  deltaTime = currentTime - lastTime;
  lastTime = currentTime;
}

void Window::clear() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Window::shouldClose() { return !glfwWindowShouldClose(window); }

const GLFWwindow *Window::getWindow() const { return window; }

void errorCallback(int code, const char *description) {
  std::cout << description << std::endl;
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods) {
  Application::getApplication().getKeys().updateState(key, action);
}

void cursorPosCallback(GLFWwindow *window, double xpos, double ypos) {
if (firstMove)
    {
        lastX = xpos;
        lastY = ypos;
        firstMove = false;
    }
  
    double xoffset = xpos - lastX;
    double yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    Camera& cam = Application::getApplication().getMainCamera();
    float& yaw = cam.getYaw();
    float& pitch = cam.getPitch();

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cam.getFront() = glm::normalize(direction);
    
    cam.update();
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
}

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {}

void windowSizeCallback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
  ScreenDim& screen = Application::getApplication().getDimensions();
  screen.width = width;
  screen.height = height;
  Application::getApplication().getMainCamera().setDimension(width, height); 
}
