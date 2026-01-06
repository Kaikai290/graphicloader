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
#include "renderer/texture_manager.h"

#include "log.h"

float vertices[] = {
  0.5, -0.5,  0.5, 0.0, 0.75,//21
 -0.5, -0.5,  0.5, 0.25, 0.75,//32
 -0.5, -0.5, -0.5, 0.25, 1.0,//43
  0.5,  0.5, -0.5, 0.25, 1.0,//53
 -0.5,  0.5, -0.5, 0.0, 1.0,//84
 -0.5,  0.5,  0.5, 0.0, 0.75,//71
  0.5,  0.5,  0.5, 0.0, 1.0,//64
  0.5, -0.5,  0.5, 0.25, 0.75,//22
  0.5,  0.5,  0.5, 0.25, 1.0,//63
 -0.5,  0.5,  0.5, 0.0, 1.0,//74
 -0.5,  0.5,  0.5, 0.25, 1.0,//73
 -0.5, -0.5, -0.5, 0.0, 0.75,//41
  0.5,  0.5, -0.5, 0.0, 1.0,//54
  0.5, -0.5, -0.5, 0.0, 0.75,//11
 -0.5, -0.5, -0.5, 0.25, 0.75,//42
  0.5, -0.5, -0.5, 0.0, 1.0,//14
  0.5,  0.5,  0.5, 0.25, 0.75,//62
  0.5, -0.5, -0.5, 0.25, 0.75,//12
 -0.5, -0.5,  0.5, 0.0, 0.75,//31
 -0.5, -0.5,  0.5, 0.25, 0.75,//32
 -0.5,  0.5, -0.5, 0.25, 1.0,//83

  0.5,  0.5, -0.5, 0.50, 1.0,//53
 -0.5,  0.5, -0.5, 0.25, 1.0,//84
 -0.5,  0.5,  0.5, 0.25, 0.75,//71
  0.5,  0.5,  0.5, 0.50, 0.75,//62
  0.5,  0.5, -0.5, 0.50, 1.0,//53
 -0.5,  0.5,  0.5, 0.25, 0.75,//71
};

// -0.5, 0.5, 0.5 71
// 0.5, 0.5, 0.5 64
// -0.5, 0.5, -0.5 83
// 0.5, 0.5, -0.5 54

unsigned int indices[] = {
  0, 1, 2, //21, 32, 43,
  21, 22, 23,//53 84 71
  3, 6, 0,//53 64 21
  7, 8, 9,//22 63 74
  10, 4, 11,//73 84 41
  12, 13, 14, //54 11 42
  15, 0, 2,//14 21 43
  24, 25, 26,//62 53 71
  17, 3, 0,//12 53 21
  18, 7, 9,//31 22 74
  19, 10, 11,//32 73 41
  20, 12, 14//83 54 42
};

float moveSpeed = 10.0f;

class AppLayer : public Layer {
public:
  bool firstPro = true;
  class VAO *vao;
  ShaderManager shader =
      ShaderManager("../../res/shaderTex.vs", "../../res/shaderTex.fs");
  Camera *camera;
  TextureManager texture = TextureManager("../../res/map.jpg");


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
        break;
      default:
          if(keys[i] == PRESSED)
            glClearColor(0.8f, 0.8f, 0.4f, 1.0f);
      };
    }
    camera->update();
  }

  virtual void update(float deltaTime) override {
    //Log::printInfo(1/deltaTime);

    glClearColor(0.3f, 0.62f, 0.89f, 1.0f);
    processInput(deltaTime);
    glm::mat4 view = camera->getView(); 

    shader.useShader();

    shader.setInt("texture0", 0);
    
    shader.setMat4("view", view);
    if(firstPro)  {
      glm::mat4 model = glm::mat4(1.0f);
      model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
      shader.setMat4("model", model);
      shader.setMat4("projection", camera->getProjection()); // needs to update if resized
      firstPro = false;
    }

    vao->bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

  }
};

/*

float vertices[] = {
  0.5, -0.5,  0.5, 0.0, 0.0,//21
 -0.5, -0.5,  0.5, 1.0, 0.0,//32
 -0.5, -0.5, -0.5, 1.0, 1.0,//43
  0.5,  0.5, -0.5, 1.0, 1.0,//53
 -0.5,  0.5, -0.5, 0.0, 1.0,//84
 -0.5,  0.5,  0.5, 0.0, 0.0,//71
  0.5,  0.5,  0.5, 0.0, 1.0,//64
  0.5, -0.5,  0.5, 1.0, 0.0,//22
  0.5,  0.5,  0.5, 1.0, 1.0,//63
 -0.5,  0.5,  0.5, 0.0, 1.0,//74
 -0.5,  0.5,  0.5, 1.0, 1.0,//73
 -0.5, -0.5, -0.5, 0.0, 0.0,//41
  0.5,  0.5, -0.5, 0.0, 1.0,//54
  0.5, -0.5, -0.5, 0.0, 0.0,//11
 -0.5, -0.5, -0.5, 1.0, 0.0,//42
  0.5, -0.5, -0.5, 0.0, 1.0,//14
  0.5,  0.5,  0.5, 1.0, 0.0,//62
  0.5, -0.5, -0.5, 1.0, 0.0,//12
 -0.5, -0.5,  0.5, 0.0, 0.0,//31
 -0.5, -0.5,  0.5, 1.0, 0.0,//32
 -0.5,  0.5, -0.5, 1.0, 1.0 //83
};

unsigned int indices[] = {
  0, 1, 2, //21, 32, 43,
  3, 4, 5,//53 84 71
  3, 6, 0,//53 64 21
  7, 8, 9,//22 63 74
  10, 4, 11,//73 84 41
  12, 13, 14, //54 11 42
  15, 0, 2,//14 21 43
  16, 3, 5,//62 53 71
  17, 3, 0,//12 53 21
  18, 7, 9,//31 22 74
  19, 10, 11,//32 73 41
  20, 12, 14//83 54 42
};


*/
