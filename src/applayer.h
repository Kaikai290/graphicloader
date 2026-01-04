#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "application.h"
#include "layer.h"
#include "camera.h"

#include "renderer/shader_manager.h"
#include "renderer/vao.h"

#include "log.h"

float vertices[] = {
 0.5, -0.5, -0.5,
 0.5, -0.5,  0.5,
-0.5, -0.5,  0.5,
-0.5, -0.5, -0.5,
 0.5,  0.5, -0.5,
 0.5,  0.5,  0.5,
-0.5,  0.5,  0.5,
-0.5,  0.5, -0.5
};

unsigned int indices[] = {
 1, 2, 3,
 4, 7, 6,
 4, 5, 1,
 1, 5, 6,
 6, 7, 3,
 4, 0, 3,
 0, 1, 3,
 5, 4, 6,
 0, 4, 1,
 2, 1, 6,
 2, 6, 3,
 7, 4, 3
};
class AppLayer : public Layer {
public:
  class VAO *vao;
  ShaderManager shader =
      ShaderManager("../../res/shader.vs", "../../res/shader.fs");
  Camera *camera;

  AppLayer(Camera& mainCamera)
    : camera(&mainCamera) { 
    vao = new VAO(&vertices, sizeof(vertices), indices, 36);

  };
  ~AppLayer() {
    delete vao;
  }

  virtual void update() override {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    


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
    
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", camera->getProjection());

    vao->bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

  }
};
