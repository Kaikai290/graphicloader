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

float moveSpeed = 10.0f;

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

  void processInput(float deltaTime) {
    auto &keys = Application::getApplication().getKeyStates();

    for (unsigned int i = 0; i != 1024; i++) {
      switch (i){
      case GLFW_KEY_ESCAPE:
        if(keys[i] == PRESSED)
          Application::getApplication().stop();
        break;
      case GLFW_KEY_A:
        if(keys[i] == PRESSED) {
          float x = deltaTime * -moveSpeed;
          camera->moveRight(x);
        }
        break;
      case GLFW_KEY_D:
        if(keys[i] == PRESSED) {
          float x = deltaTime * moveSpeed;
          camera->moveRight(x);
        }
        break;
      case GLFW_KEY_W:
        if(keys[i] == PRESSED) {
          float z = deltaTime * moveSpeed;
          camera->moveForward(z);
        }
        break;
      case GLFW_KEY_S:
        if(keys[i] == PRESSED) {
          float z = deltaTime * -moveSpeed;
          camera->moveForward(z);
        }
        break;
      case GLFW_KEY_SPACE:
        if(keys[i] == PRESSED) {
          float y = deltaTime * moveSpeed;
          camera->moveUp(y);
        }
        break;
      case GLFW_KEY_LEFT_SHIFT:
        if(keys[i] == PRESSED) {
          float y = deltaTime * -moveSpeed;
          camera->moveUp(y);
        }
      default:
          if(keys[i] == PRESSED)
            glClearColor(0.8f, 0.8f, 0.4f, 1.0f);
      };
    }
    camera->update();
  }

  virtual void update(float deltaTime) override {
    Log::printInfo(1/deltaTime);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    glClearColor(0.2f, 0.7f, 0.4f, 1.0f);
    processInput(deltaTime);
    glm::mat4 view = camera->getView(); 

    shader.useShader();
    
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", camera->getProjection());

    vao->bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

  }
};
