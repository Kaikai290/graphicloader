#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"

#include <iostream>
#include <memory>
#include <vector>

#include "application.h"
#include "camera.h"
#include "log.h"

namespace LZ {
void errorCallback(int code, const char *description);

static Application *app = nullptr;

Application::Application(ApplicationSpec spec) : spec(spec) {
  if (glfwInit())
    Log::printInfo("Initalize GLFW");

  glfwSetErrorCallback(errorCallback);
  app = this;
  window = std::make_shared<Window>();
  if (window) {
    Log::printInfo("Window Created");
  }
  window->init(spec);

  mainCamera = std::make_shared<LazyCamera>(spec.dimensions.width, spec.dimensions.height);
  if (mainCamera) {
    Log::printInfo("Main Camera Created");
  }
  prevTime = glfwGetTime();
}

Application::~Application() {
  Log::printInfo("Main Camera Deleted"); //move to lazy cam class
  window->shutdown();
  glfwTerminate();
}

Application &Application::getApplication() { return *app; }

ScreenDim &Application::getDimensions() { return spec.dimensions; }

LazyCamera &Application::getMainCamera() { return *mainCamera; }

void Application::run() {
  running = true;

  while (running) {
    calculateTime();

    running = window->shouldClose();

    window->pollEvents();

    window->clear();

    for (const std::unique_ptr<Layer> &layer : layers) {
      layer->update(deltaTime);
    }

    for (const std::unique_ptr<Layer> &layer : layers) {
      layer->render();
    }
    for (const std::unique_ptr<Overlay> &overlay : overlays) {
      overlay->update(deltaTime);
    }

    for (const std::unique_ptr<Overlay> &overlay : overlays) {
      overlay->render();
    }

    window->update();
  }
}

void Application::stop() { running = false; }

void Application::calculateTime() {
  float currTime = glfwGetTime();
  deltaTime = currTime - prevTime;
  prevTime = currTime;
}

Key &Application::getKeys() { return keys; }

std::vector<unsigned int> &Application::getKeyStates() {
  return keys.getStates();
}

std::vector<unsigned int> &Application::getPrevKeyStates() {
  return keys.getPrevStates();
}
} // namespace LZ
