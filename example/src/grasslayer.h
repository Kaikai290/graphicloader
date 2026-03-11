
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "application.h"
#include "camera.h"
#include "layer.h"

#include "renderer/shader_manager.h"

static const GLfloat grass_blade[] = {-0.3f, 0.0f, 0.0f,   0.0f, 0.0f, 0.3f,
                                      -0.2f,  1.3f, 0.0f, 2.3f, 0.0f,   3.3f};

static float moveSpeed = 10.0f;

class GrassLayer : public LZ::Layer {
public:
  ShaderManager grassShader = ShaderManager();
  std::shared_ptr<LZ::LazyCamera> camera;
  GLuint grassVAO, grassVBO;

  GrassLayer() {
    grassShader.setVertex("../res/grassShader.vs");
    grassShader.setFragment("../res/grassShader.fs");
    grassShader.createShader();


    glCreateVertexArrays(1, &grassVAO);
    glBindVertexArray(grassVAO);

    glCreateBuffers(1, &grassVBO);
    glNamedBufferStorage(grassVBO, sizeof(grass_blade), grass_blade,
                         GL_MAP_READ_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, grassVBO);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
  }

  ~GrassLayer() { }

  void setup(std::shared_ptr<LZ::LazyCamera> mainCamera) override {
    camera = mainCamera;
  }

  void processInput(float deltaTime) {
    auto &keys = LZ::Application::getApplication().getKeyStates();

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

  virtual void update(float deltaTime) override {
    // Log::printInfo(1/deltaTime);

    glClearColor(0.3f, 0.62f, 0.89f, 1.0f);
    processInput(deltaTime);

    glm::mat4 view = camera->getView();


    glm::mat4 model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    grassShader.useShader();

    grassShader.setMat4("view", view);
    grassShader.setMat4("model", model);
    grassShader.setMat4("projection",
                        camera->getProjection()); // needs to update if resized

    glBindVertexArray(grassVAO);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 6,  1024 * 1024);
  }
};

