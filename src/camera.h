#ifndef CAMERA_H
#define CAMERA_H

#include "glm/ext/vector_float3.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
  Camera(int width, int height);

  void update();

  glm::mat4& getProjection() ;
  glm::mat4& getView() ;

  glm::vec3& getPosistion();
  float& getPitch() ;
  float& getYaw() ;

  glm::vec3& getFront();

  void move(float x, float y, float z);

  void moveForward(float y);
  void moveRight(float x);
  void moveUp(float z);

  void setDimension(int width, int height);
  void setProjection(glm::mat4 pro);
  void updateProjection();

private:
  glm::mat4 projection;

  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
  glm::vec3 cameraRight;

  glm::vec3 worldUp= glm::vec3(0.0f, 1.0f, 0.0f);

  glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
;

  float yaw = -90.0f;
  float pitch = 0.0f;

  float sensitivity = 0.1f;

  int screenWidth;
  int screenHeight;
  float aspectRatio;
};

#endif
