#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "application.h"
#include "camera.h"
#include "event.h"
#include "glm/detail/qualifier.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"
#include "layer.h"

#include "renderer/shader_manager.h"
#include "renderer/texture_manager.h"
#include "renderer/vao.h"

#include "grasslayer.h"
#include "log.h"


#define TILE_SIZE 100.0f

class HeightMapLayer : public LZ::Layer {
public:
  ShaderManager shader = ShaderManager();
  std::shared_ptr<LZ::LazyCamera> camera;
  TextureManager heightMap = TextureManager("../res/iceland.jpg");
  GLuint VAO, VBO;
  bool heightMapSetting = true;

  HeightMapLayer() {
    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_POLYGON_SMOOTH);

    glEnable(GL_MULTISAMPLE);


    shader.setVertex("../res/heightmapShader.vs");
    shader.setFragment("../res/heightmapShader.fs");
    shader.setTessControl("../res/heightmapShader.tc");
    shader.setTessEval("../res/heightmapShader.te");
    shader.createShader();

    float squareVertices[] = {
    0.0f, 0.0f,0.0f, 
    0.0f,  0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     1.0f, 0.0f , 1.0f
  };
    glCreateVertexArrays(1, &VAO);

    glCreateBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(squareVertices), squareVertices, GL_STATIC_DRAW); 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

  }
  ~HeightMapLayer() {}

  void setup(std::shared_ptr<LZ::LazyCamera> mainCamera) override {
    camera = mainCamera;
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), camera->getAspectRatio(), 0.1f, 10000.0f);
    camera->setProjection(projection);
  }

  virtual void event(LZ::Event& event) override {
    switch (event.getEventType()) {
      case LZ::None:
        break;
      case LZ::Key:
        std::cout << static_cast<LZ::KeyEvent *>(&event)->getKeyCode() << std::endl;
        break;
      case LZ::MouseMove:
        std::cout << static_cast<LZ::MouseMoveEvent *>(&event)->getXpos() << static_cast<LZ::MouseMoveEvent *>(&event)->getYpos() << std::endl;
        break;
    }
  }

  virtual void update(float deltaTime) override {

    glClearColor(0.3f, 0.62f, 0.89f, 1.0f);
    processInput(deltaTime);

    glm::mat4 view = camera->getView();

    shader.useShader();

    shader.setInt("texture0", 0);

    shader.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4("model", model);
    shader.setMat4("projection",
                   camera->getProjection()); // needs to update if resized
    shader.setFloat("tiling", TILE_SIZE);
    shader.setFloat("width", (float)heightMap.width);
    shader.setFloat("height", (float)heightMap.height);
    shader.setBool("heightMap", heightMapSetting);
    glBindVertexArray(VAO);
    glDrawArraysInstanced(GL_PATCHES, 0, 4, TILE_SIZE * TILE_SIZE);
  }

  void processInput(float deltaTime) {
    auto &inputs = LZ::Application::getApplication().getInputs();
    auto &keys = inputs.getStates(); 
    float moveSpeed = 50;
    static bool wireframe = false;
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
          if(wireframe) {
              glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
              wireframe = false;
            } else {
              glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
              wireframe = true;
            }
          inputs.keyTap(i);
        }
        break;
      case GLFW_KEY_T:
        if (keys[i] == PRESSED) {
            if(heightMapSetting) {
              heightMapSetting = false;
            }
            else { 
              heightMapSetting = true;
            }
          inputs.keyTap(i);
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
