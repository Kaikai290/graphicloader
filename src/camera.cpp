#include "camera.h"
#include <iostream>
namespace LZ {
LazyCamera::LazyCamera(int width, int height)
  :screenWidth(width), screenHeight(height){
  aspectRatio = (float)width/(float)height;
  projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 100.0f);
  update();
}

void LazyCamera::update() {
  glm::vec3 front;
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  cameraFront = glm::normalize(front);
  cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
  cameraUp    = glm::normalize(glm::cross(cameraRight, cameraFront));

  view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void LazyCamera::turn(float xOffset, float yOffset) {
  yaw += (sensitivity * xOffset);
  pitch += (sensitivity * yOffset);

  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;
  update();
}

glm::mat4& LazyCamera::getProjection(){
  return projection;
}

glm::mat4& LazyCamera::getView(){
  return view;
}

glm::vec3& LazyCamera::getPosistion() {
  return cameraPos;
}

float& LazyCamera::getPitch() {
  return pitch;
}

float& LazyCamera::getYaw() {
  return yaw;
}

glm::vec3& LazyCamera::getFront() {
  return cameraFront;
}

void LazyCamera::move(float x, float y, float z) {
  cameraPos.x = x;
  cameraPos.y = y;
  cameraPos.z = z;
}

void LazyCamera::moveForward(float z) {
  cameraPos += cameraFront * z;
}

void LazyCamera::moveRight(float x) {
  cameraPos += cameraRight * x;
}

void LazyCamera::moveUp(float y) {
  cameraPos += cameraUp * y;
}

void LazyCamera::setDimension(int width, int height) {
  screenWidth = width;
  screenHeight = height;
  aspectRatio = (float)width/(float)height;
  updateProjection();
}

void LazyCamera::updateProjection() {
  projection = glm::perspective(glm::radians(90.0f), aspectRatio, 0.1f, 100.0f);
}

void LazyCamera::setProjection(glm::mat4 pro) {
  projection = pro;
}
}
