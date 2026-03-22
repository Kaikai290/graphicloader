#include <GLFW/glfw3.h>

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "application.h"
#include "camera.h"

#include "glm/detail/qualifier.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/ext/vector_float4.hpp"
#include "glm/gtc/random.hpp"

#include "key.h"
#include "layer.h"

#include "renderer/shader_manager.h"
#include "renderer/texture_manager.h"
#include "renderer/vao.h"

#include "grasslayer.h"
#include "log.h"


enum
{
    WORKGROUP_SIZE  = 256,
    NUM_WORKGROUPS  = 64,
    FLOCK_SIZE      = (NUM_WORKGROUPS * WORKGROUP_SIZE)
};

struct flockMember {
  glm::vec3 position;
  unsigned int :32;
  glm::vec3 velocity;
  unsigned int :32;
};

class FlockingLayer : public LZ::Layer {
public:
  ShaderManager shader = ShaderManager();
  ShaderManager computeShader = ShaderManager();
  std::shared_ptr<LZ::LazyCamera> camera;
  TextureManager heightMap = TextureManager("../res/iceland.jpg");
  GLuint VAO[2], planeGeo, flockBuffer[2];
  bool heightMapSetting = true;

  FlockingLayer() {
    shader.setVertex("../res/flockingShader.vs");
    shader.setFragment("../res/flockingShader.fs");
    shader.createShader();
    computeShader.setCompute("../res/flockingShader.cs");
    computeShader.createShader();

    float plane[] = {
            -5.0f, 1.0f, 0.0f,
            -1.0f, 1.5f, 0.0f ,
            -1.0f, 1.5f, 7.0f ,
            0.0f, 0.0f, 0.0f ,
            0.0f, 0.0f, 10.0f ,
            1.0f, 1.5f, 0.0f ,
            1.0f, 1.5f, 7.0f ,
            5.0f, 1.0f, 0.0f ,

            // Normals
            0.0f , 0.0f, 0.0f,
            0.0f , 0.0f, 0.0f,
            0.107f, -0.859f, 0.00f ,
            0.832f, 0.554f, 0.00f ,
            -0.59f, -0.395f, 0.00f ,
            -0.832f, 0.554f, 0.00f ,
            0.295f, -0.196f, 0.00f ,
            0.124f, 0.992f, 0.00f ,
    };

    glGenBuffers(2, flockBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, flockBuffer[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, FLOCK_SIZE * sizeof(flockMember), NULL, GL_DYNAMIC_COPY);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, flockBuffer[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, FLOCK_SIZE * sizeof(flockMember), NULL, GL_DYNAMIC_COPY);

    glGenBuffers(1, &planeGeo);
    glBindBuffer(GL_ARRAY_BUFFER, planeGeo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plane), plane, GL_STATIC_DRAW);

    glGenVertexArrays(2, VAO);

    for(int i = 0; i != 2; i++) {
      glBindVertexArray(VAO[i]);
      glBindBuffer(GL_ARRAY_BUFFER, planeGeo);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)(8*sizeof(float)*3));

      glBindBuffer(GL_ARRAY_BUFFER, flockBuffer[i]);
      glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(flockMember), NULL);
      glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(flockMember), (void *)sizeof(glm::vec4));
      glVertexAttribDivisor(2, 1);
      glVertexAttribDivisor(3, 1);

      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);
      glEnableVertexAttribArray(3);
    }

    glBindBuffer(GL_ARRAY_BUFFER, flockBuffer[0]);

    flockMember* ptr = reinterpret_cast<flockMember *> (glMapBufferRange(GL_ARRAY_BUFFER, 0, FLOCK_SIZE * sizeof(flockMember), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));

    for(int i = 0; i < FLOCK_SIZE; i++) {
      float x = glm::linearRand(-10.0, 10.0) * 10;
      float y = glm::linearRand(-10.0, 10.0) * 10;
      float z = glm::linearRand(-10.0, 10.0) * 10;
      float dx = glm::linearRand(-10.0, 10.0);
      float dy = glm::linearRand(-10.0, 10.0);
      float dz = glm::linearRand(-10.0, 10.0);
      ptr[i].position = glm::vec3(x, y, z);
      ptr[i].velocity = glm::vec3(dx, dy, dz);
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
    glDepthFunc(GL_LEQUAL);
  }
  ~FlockingLayer() {}

  void setup(std::shared_ptr<LZ::LazyCamera> mainCamera) override {
    camera = mainCamera;
    glm::mat4 projection = glm::perspective(glm::radians(90.0f), camera->getAspectRatio(), 0.1f, 10000.0f);
    camera->setProjection(projection);
  }

  virtual void update(float deltaTime) override {
    LZ::Log::printInfo(1/deltaTime);

    glClearColor(0.3f, 0.62f, 0.89f, 1.0f);
    processInput(deltaTime);

    computeShader.useShader();

    computeShader.setFloat("timestep", deltaTime);

    glm::vec3 goal = glm::vec3(3.0f*deltaTime, 5.0f*deltaTime, 6.0f*deltaTime);

    computeShader.setVec3("goal", goal);
    static int i = 0;

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, flockBuffer[i]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, flockBuffer[(i+1)%2]);
    
    glDispatchCompute(NUM_WORKGROUPS, 1, 1);

    glm::mat4 view = camera->getView();

    shader.useShader();

    shader.setInt("texture0", 0);

    shader.setMat4("view", view);

    glm::mat4 model = glm::mat4(1.0f);
    shader.setMat4("model", model);
    shader.setMat4("projection",
                   camera->getProjection()); // needs to update if resized

    glBindVertexArray(VAO[i]);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 8, FLOCK_SIZE);
     i = (i+1) % 2;
  }

  void processInput(float deltaTime) {
    auto &inputs = LZ::Application::getApplication().getKeyStates();
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
        }
        break;
      case GLFW_KEY_T:
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
