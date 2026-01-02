#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "application.h"
#include "layer.h"

#include "renderer/shader_manager.h"
#include "renderer/vao.h"

float triangleVertices1[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.75f, 0.0f
    };
unsigned int triangleIndices1[] = {
  0, 1, 2
};

class AppLayer : public Layer {
public:
  class VAO *vao;
  ShaderManager shader =
      ShaderManager("../../res/shader.vs", "../../res/shader.fs");
  AppLayer() { 
    vao = new VAO(&triangleVertices1, sizeof(triangleVertices1), triangleIndices1, 3);

  };
  ~AppLayer() {
    delete vao;
  }

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
    shader.useShader();
    vao->bind();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
  }
};
