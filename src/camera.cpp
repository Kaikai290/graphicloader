#include "camera.h"

#include "log.h"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(int width, int height)
  :screenWidth(width), screenHeight(height){
  aspectRatio = (float)width/(float)height;
  projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 100.0f);
  update();
}

void Camera::update() {
  glm::vec3 front;
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  cameraFront = glm::normalize(front);
  cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
  cameraUp    = glm::normalize(glm::cross(cameraRight, cameraFront));

  view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

glm::mat4& Camera::getProjection(){
  return projection;
}

glm::mat4& Camera::getView(){
  return view;
}

float& Camera::getPitch() {
  return pitch;
}

float& Camera::getYaw() {
  return yaw;
}

glm::vec3& Camera::getFront() {
  return cameraFront;
}

void Camera::move(float x, float y, float z) {
  cameraPos.x = x;
  cameraPos.y = y;
  cameraPos.z = z;
}

void Camera::moveForward(float z) {
  cameraPos += cameraFront * z;
}

void Camera::moveRight(float x) {
  cameraPos += cameraRight * x;
}

void Camera::moveUp(float y) {
  cameraPos += cameraUp * y;
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
