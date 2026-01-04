#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "application.h"
#include "camera.h"
#include "log.h"

void errorCallback(int code, const char* description);

static Application* app = nullptr;

Application::Application(ApplicationSpec spec) 
  : spec(spec) {
  if (glfwInit())
    Log::printInfo("Initalize GLFW");
  glfwSetErrorCallback(errorCallback);
  app = this;
  window = new Window();
  if(window) {
    Log::printInfo("Window Created");
  }
  window->init(spec);
  mainCamera = new Camera(spec.dimensions.width, spec.dimensions.height);
  if(mainCamera) {
    Log::printInfo("Main Camera Created");
  }
}

Application::~Application() {
  delete window;
  Log::printInfo("Window Deleted");
  delete mainCamera;
  Log::printInfo("Main Camera Deleted");
  glfwTerminate();
}

Application& Application::getApplication() {
  return *app;
}

ScreenDim& Application::getDimensions() {
  return spec.dimensions;
}

Camera& Application::getMainCamera(){
  return *mainCamera;
}


void Application::run() {
  running = true;

  while(running) {
    running = window->shouldClose();
    window->clear();

    for(auto layer: layers){
      layer->update();
    }

    for(auto layer: layers) {
      layer->render();
    }

    window->update();
  }
}

void Application::stop() {
  running = false;
}

void Application::pushLayer(Layer* layer) {
  layers.push_back(layer);
}

Key& Application::getKeys() {
  return keys;
}

std::vector<unsigned int>& Application::getKeyStates() {
  return keys.getStates();
}

std::vector<unsigned int>& Application::getPrevKeyStates() {
  return keys.getPrevStates();
}
