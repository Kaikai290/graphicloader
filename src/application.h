#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>
#include <memory>
#include <vector>

#include "layer.h"
#include "overlay.h"
#include "window.h"

#include "camera.h"
#include "key.h"

namespace LZ {
struct ScreenDim {
  int width = 900;
  int height = 600;
  float resolution = (float)width / (float)height;

  void setDimension(int x, int y) {
    width = x;
    height = y;
    resolution = (float)width / (float)height;
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
  std::shared_ptr<Window> window;
  std::shared_ptr<LazyCamera> mainCamera;

  float deltaTime = 0.0f;
  float prevTime;

  Key keys;

  std::vector<std::unique_ptr<Layer>> layers;
  std::vector<std::unique_ptr<Overlay>> overlays;

  bool running = false;

public:
  Application(ApplicationSpec spec);
  ~Application();

  static Application &getApplication();

  ScreenDim &getDimensions();

  LazyCamera &getMainCamera();

  void run();
  void stop();
  void calculateTime();

  template <typename TLayer> void pushLayer() {
    layers.push_back(std::make_unique<TLayer>());
    layers.back()->setup(mainCamera);
  }
  template <typename TLayer> void pushLayer(LazyCamera &camera) {
    layers.push_back(std::make_unique<TLayer>());
  }
  template <typename TOverlay> void pushOverlay() {
    overlays.push_back(std::make_unique<TOverlay>());
  }

  Key &getKeys();
  std::vector<unsigned int> &getKeyStates();
  std::vector<unsigned int> &getPrevKeyStates();
};
} // namespace LZ
#endif
