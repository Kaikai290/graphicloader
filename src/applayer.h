#include <GL/gl.h>
#include <iostream>

#include <GLFW/glfw3.h>

#include "application.h"
#include "layer.h"

class AppLayer : public Layer {
  virtual void update() override {
    glClearColor(0.2f, 0.7f, 0.4f, 1.0f);
    auto &keys = Application::getApplication().getKeyStates();
    for (unsigned int i = 0; i != 1024; i++) {
      switch (i){
      case GLFW_KEY_ESCAPE:
        if(keys[i] == PRESSED)
          Application::getApplication().stop();
        break;
      default:
          if(keys[i] == PRESSED)
            glClearColor(0.8f, 0.8f, 0.4f, 1.0f);
      };
    }
  }
};
