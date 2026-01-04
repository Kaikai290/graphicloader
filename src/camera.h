#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
  Camera(int width, int height);

  glm::mat4 getProjection();

  void setDimension(int width, int height);
  void setProjection(glm::mat4 pro);
  void updateProjection();

private:
  glm::mat4 projection;
  int screenWidth;
  int screenHeight;
  float aspectRatio;
};


#endif
