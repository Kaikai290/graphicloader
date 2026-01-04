#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>
#include <vector>

#include "window.h"
#include "layer.h"

#include "camera.h"
#include "key.h"

struct ScreenDim {
  int width = 900;
  int height = 600;
  float resolution = (float)width/(float)height; 

  void setDimension(int x, int y) {
    width = x;
    height = y;
    resolution = (float)width/(float)height; 
  }
};

struct ApplicationSpec {
  ScreenDim dimensions;
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
  Camera *mainCamera;

  float deltaTime = 0.0f;
  float prevTime;

  Key keys;

  std::vector<Layer *> layers;

  bool running = false;

public:
  Application(ApplicationSpec spec);
  ~Application();

  static Application& getApplication();

  ScreenDim& getDimensions();
  
  Camera& getMainCamera();

  void run();
  void stop();
  void calculateTime();

  void pushLayer(Layer *layer);

  Key& getKeys();
  std::vector<unsigned int>& getKeyStates();
  std::vector<unsigned int>& getPrevKeyStates();
};

#endif
