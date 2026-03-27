#ifndef WINDOW_H
#define WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cstdint>
#include <string>

namespace LZ {
struct ApplicationSpec;

class Window {
private:
  GLFWwindow *window;


public:
  Window();
  ~Window();

  void init(ApplicationSpec spec);
  void shutdown();
  void pollEvents();
  void update();
  void clear();
  bool shouldClose();

  const GLFWwindow* getWindow() const;
};
}
#endif
