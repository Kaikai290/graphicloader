#include "application.h"
#include <GLFW/glfw3.h>

static Application* app = nullptr;

Application::Application(WindowSpec spec) 
  : spec(spec) {
  app = this;
  window.init(spec);
}

Application::~Application() {}

void Application::run() {
  running = true;

  while(running) {
    running = window.shouldClose();
    window.update();
  }

}
