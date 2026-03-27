

#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h> 

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "application.h"
#include "camera.h"
#include "layer.h"

#include "renderer/shader_manager.h"
#include "renderer/texture_manager.h"
#include "renderer/vao.h"

#include "grasslayer.h"
#include "log.h"

static const GLfloat triangle_vertices[] = 
  {-0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
    0.5f, 0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,
  -0.5f, 0.5f, 0.0f,
   };

static const GLfloat instance_colors[] = {1.0f, 0.0f, 0.0f, 1.0f, 
                                          0.0f, 1.0f, 0.0f, 1.0f, 
                                          0.0f, 0.0f, 1.0f, 1.0f,
                                          1.0f, 0.0f, 1.0f, 1.0f,
                                          1.0f, 1.0f, 0.0f, 1.0f};

static const GLfloat instance_positions[] = {
    -2.0f, -2.0f, 0.0f, 1.0f, 
    2.0f,  -2.0f, 0.0f, 1.0f,
    2.0f,  2.0f,  0.0f, 1.0f, 
    -2.0f, 2.0f,  0.0f, 1.0f,
    0.0f, 0.0f, 0.0f, 1.0f};

class InstanceLayer : public LZ::Layer {
public:
  bool firstPro = true;
  ShaderManager shader = ShaderManager();
  std::shared_ptr<LZ::LazyCamera> camera;
  GLuint insVAO, insVBO;

  InstanceLayer() {
    shader.setVertex("../res/instanceShader.vs");
    shader.setFragment("../res/instanceShader.fs");
    shader.createShader();

    glGenVertexArrays(1, &insVAO);
    glBindVertexArray(insVAO);
    glGenBuffers(1, &insVBO);
    glBindBuffer(GL_ARRAY_BUFFER, insVBO);
    glBufferStorage(GL_ARRAY_BUFFER, sizeof(triangle_vertices) + sizeof(instance_colors) + sizeof(instance_positions), NULL, GL_DYNAMIC_STORAGE_BIT);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(triangle_vertices), triangle_vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), sizeof(instance_colors), instance_colors);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(triangle_vertices) +sizeof(instance_colors), sizeof(instance_positions), instance_positions);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)sizeof(triangle_vertices));
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(sizeof(triangle_vertices) + sizeof(instance_colors)));

    glEnableVertexAttribArray(0);    
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribDivisor(1,2);
    glVertexAttribDivisor(2,1);
  }

  ~InstanceLayer() {}

  void setup(std::shared_ptr<LZ::LazyCamera> mainCamera) override {
    camera = mainCamera;
  }

  virtual void update(float deltaTime) override {
    // Log::printInfo(1/deltaTime);

    glClearColor(0.3f, 0.62f, 0.89f, 1.0f);
    processInput(deltaTime);

    glm::mat4 view = camera->getView();

    shader.useShader();
    shader.setInt("texture0", 0);

    shader.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    shader.setMat4("model", model);
    shader.setMat4("projection",
                   camera->getProjection()); // needs to update if resized
    glBindVertexArray(insVAO);
    glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, 6, 4, 0);
  }

void processInput(float deltaTime) {
    auto &inputs = LZ::Application::getApplication().getInputs();
    auto &keys = inputs.getStates(); 
    for (unsigned int i = 0; i != 1024; i++) {
      switch (i) {
      case GLFW_KEY_ESCAPE:
        if (keys[i] == PRESSED)
          LZ::Application::getApplication().stop();
        break;
      case GLFW_KEY_A:
        if (keys[i] == PRESSED) {
          float x = deltaTime * -moveSpeed;
          camera->moveRight(x);
        }
        break;
      case GLFW_KEY_D:
        if (keys[i] == PRESSED) {
          float x = deltaTime * moveSpeed;
          camera->moveRight(x);
        }
        break;
      case GLFW_KEY_W:
        if (keys[i] == PRESSED) {
          float z = deltaTime * moveSpeed;
          camera->moveForward(z);
        }
        break;
      case GLFW_KEY_S:
        if (keys[i] == PRESSED) {
          float z = deltaTime * -moveSpeed;
          camera->moveForward(z);
        }
        break;
      case GLFW_KEY_R:
        if (keys[i] == PRESSED) {
        }
        break;
      case GLFW_KEY_SPACE:
        if (keys[i] == PRESSED) {
          float y = deltaTime * moveSpeed;
          camera->moveUp(y);
        }
        break;
      case GLFW_KEY_LEFT_SHIFT:
        if (keys[i] == PRESSED) {
          float y = deltaTime * -moveSpeed;
          camera->moveUp(y);
        }
        break;
      default:
        if (keys[i] == PRESSED)
          glClearColor(0.0f, 0.0f, 0.0f, 0.1f);
      };
    }
    camera->update();
  }
}

;

