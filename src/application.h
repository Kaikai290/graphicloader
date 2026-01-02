#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>
#include <vector>

#include "layer.h"
#include "window.h"
#include "key.h"

struct ApplicationSpec {
  int width = 900;
  int height = 600;
  std::string title = "default app";
  bool mouseLock = false;
  bool rawMouseMoition = false;
  int resizable = GLFW_TRUE;
  int windowFocused = GLFW_TRUE;
  int centerCusor = GLFW_FALSE;
};

class Application {
private:
  ApplicationSpec spec;
  Window *window;

  Key keys;

  std::vector<Layer *> layers;

  bool running = false;

public:
  Application(ApplicationSpec spec);
  ~Application();

  static Application& getApplication();

  void run();
  void stop();

  void pushLayer(Layer *layer);

  Key& getKeys();
  std::vector<unsigned int>& getKeyStates();
  std::vector<unsigned int>& getPrevKeyStates();
};

#endif
