#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

#include "application.h"

void errorCallback(int code, const char* description);

static Application* app = nullptr;

Application::Application(ApplicationSpec spec) 
  : spec(spec) {
  if (glfwInit())
    std::cout << "Initalize GLFW" << std::endl;
  glfwSetErrorCallback(errorCallback);
  app = this;
  window = new Window();
  window->init(spec);
}

Application::~Application() {
  delete window;
  glfwTerminate();
}

Application& Application::getApplication() {
  return *app;
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
