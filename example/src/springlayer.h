#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "application.h"
#include "camera.h"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"
#include "layer.h"

#include "renderer/shader_manager.h"
#include "renderer/texture_manager.h"
#include "renderer/vao.h"

#include "grasslayer.h"
#include "log.h"

#define TOTAL_SPRINGS 10000

class SpringLayer : public LZ::Layer {
public:
  ShaderManager shader = ShaderManager();
  ShaderManager updateShader = ShaderManager();
  std::shared_ptr<LZ::LazyCamera> camera;
  GLuint springVAO[2], springVBO[5], springTBO[2];

  SpringLayer() {
    shader.setVertex("../res/springShader.vs");
    shader.setFragment("../res/springShader.fs");
    shader.createShader();

    updateShader.setVertex("../res/springShaderUpdate.vs");
    updateShader.createShader();
    static const char* tf_varyings[] = 
      {"tfPos_mass",
      "tfVelocity"};
    glTransformFeedbackVaryings(updateShader.ShaderProgram, 2, tf_varyings, GL_SEPARATE_ATTRIBS);
    glLinkProgram(updateShader.ShaderProgram);

    glm::vec4 pos_mass[TOTAL_SPRINGS];
    glm::vec3 velocity[TOTAL_SPRINGS];
    glm::tvec4<GLint> connections[TOTAL_SPRINGS];

    int rowLength = 100;
    int height = TOTAL_SPRINGS/rowLength;
    for(int i = 0; i != TOTAL_SPRINGS; i++) {
      int x = i % rowLength;
      int y = i / rowLength;
      pos_mass[i] = glm::vec4(x, y, 0.0f, 1.0f);
      velocity[i] = glm::vec3(0.0f);

      connections[i] = glm::ivec4(-1);
      if(y != height - 1) {
        if(x != 0)
          connections[i][0] = i - 1;
        if(x != (rowLength - 1))
          connections[i][1] = i + 1;
        if(y != 0)
          connections[i][2] = i - rowLength;
        if(y != (height - 1))
          connections[i][3] = i + rowLength;
      }
    }
    velocity[0].y = -5;
    glGenVertexArrays(2, springVAO);
    glGenBuffers(5, springVBO);
    for (int i = 0; i != 2; i++) {
      glBindVertexArray(springVAO[i]);

      glBindBuffer(GL_ARRAY_BUFFER, springVBO[i]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * TOTAL_SPRINGS, pos_mass,
                   GL_DYNAMIC_COPY);
      glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), NULL);
      glEnableVertexAttribArray(0);

      glBindBuffer(GL_ARRAY_BUFFER, springVBO[2+i]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * TOTAL_SPRINGS, velocity,
                   GL_DYNAMIC_COPY);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), NULL);
      glEnableVertexAttribArray(1);

      glBindBuffer(GL_ARRAY_BUFFER, springVBO[4]);
      glBufferData(GL_ARRAY_BUFFER, sizeof(glm::tvec4<GLint>) * TOTAL_SPRINGS, connections,
                   GL_STATIC_DRAW);
      glVertexAttribIPointer(2, 4, GL_INT, 0, NULL);
      glEnableVertexAttribArray(2);
    }

    glGenTextures(2, springTBO);
    glBindTexture(GL_TEXTURE_BUFFER, springTBO[0]);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, springVBO[0]);
    glBindTexture(GL_TEXTURE_BUFFER, springTBO[1]);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, springVBO[1]);
  }

  ~SpringLayer() {}

  void setup(std::shared_ptr<LZ::LazyCamera> mainCamera) override {
    camera = mainCamera;
  }

  virtual void update(float deltaTime) override {
    // Log::printInfo(1/deltaTime);

    glClearColor(0.3f, 0.62f, 0.89f, 1.0f);
    processInput(deltaTime);

    glm::mat4 view = camera->getView();

    shader.useShader();

    shader.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4("model", model);
    shader.setMat4("projection",
                   camera->getProjection()); // needs to update if resized
    static int iter = 0;
    updateShader.useShader();
    updateShader.setFloat("t", deltaTime);
    glEnable(GL_RASTERIZER_DISCARD);

    if (iter == 0) {
      glBindVertexArray(springVAO[0]);
      glBindTexture(GL_TEXTURE_BUFFER, springTBO[0]);
      glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, springVBO[1]);
      glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, springVBO[3]);
      glBeginTransformFeedback(GL_POINTS);
      glDrawArrays(GL_POINTS, 0, TOTAL_SPRINGS);
      glEndTransformFeedback();
      iter = 1;
    } else {
      glBindVertexArray(springVAO[1]);
      glBindTexture(GL_TEXTURE_BUFFER, springTBO[1]);
      glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, springVBO[0]);
      glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 1, springVBO[2]);
      glBeginTransformFeedback(GL_POINTS);
      glDrawArrays(GL_POINTS, 0, TOTAL_SPRINGS);
      glEndTransformFeedback();
      iter = 0;
    }

    glDisable(GL_RASTERIZER_DISCARD);
    shader.useShader();
    glPointSize(2.0f);
    glDrawArrays(GL_POINTS, 0, TOTAL_SPRINGS);
  }

  void processInput(float deltaTime) {
    auto &inputs = LZ::Application::getApplication().getKeyStates();
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
