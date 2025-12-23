#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "application.h"

static Application* app = nullptr;

Application::Application(ApplicationSpec spec) 
  : spec(spec) {
  if (glfwInit())
    std::cout << "Initalize GLFW" << std::endl;
  app = this;
  window.init(spec);
}

Application::~Application() {
  glfwTerminate();
}

Application& Application::getApplication() {
  return *app;
}

void Application::run() {
  running = true;

  while(running) {
    running = window.shouldClose();

    for(auto layer: layers){
      layer->update();
    }

    for(auto layer: layers) {
      layer->render();
    }

    window.update();
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
