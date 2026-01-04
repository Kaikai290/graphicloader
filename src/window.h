#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>

struct ApplicationSpec;

class Window {
private:
  GLFWwindow *window;


  double deltaTime = 0.0f;
  double lastTime = 0.0f;
public:
  Window();
  ~Window();

  void init(ApplicationSpec spec);
  void update();
  void clear();
  bool shouldClose();

  const GLFWwindow* getWindow() const;
};

#endif
