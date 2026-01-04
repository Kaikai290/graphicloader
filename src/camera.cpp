#include "camera.h"

#include "log.h"

Camera::Camera(int width, int height)
  :screenWidth(width), screenHeight(height){
  aspectRatio = (float)width/(float)height;
  projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 100.0f);
}

glm::mat4 Camera::getProjection() {
  return projection;
}

void Camera::setDimension(int width, int height) {
  screenWidth = width;
  screenHeight = height;
  aspectRatio = (float)width/(float)height;
  updateProjection();
}

void Camera::updateProjection() {
  projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 100.0f);
}

void Camera::setProjection(glm::mat4 pro) {
  projection = pro;
}
