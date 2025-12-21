#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <string>

struct WindowSpec {
  int width = 900;
  int height = 600;
  std::string title = "default app";


};

class Window {
private:
  GLFWwindow *window;

public:
  Window();
  ~Window();

  void init(WindowSpec spec);
  void update();
  bool shouldClose();

  const GLFWwindow* getWindow() const;
};

#endif
