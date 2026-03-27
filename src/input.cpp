#include <GLFW/glfw3.h>
#include <iostream>

#include "input.h"

namespace LZ {
Input::Input() : state(1024, RELEASED), prevState(1024, RELEASED){};

Input::~Input() {};

void Input::updateState(int key, int action) {
  if(key > state.size()) {
    std::cout << "Input out of range" << std::endl;
    return;
  }

  if(action == GLFW_PRESS) {
    state[key] = PRESSED;
  }

  if(action == GLFW_RELEASE) {
    state[key] = RELEASED;
  }
}

void Input::updatePrevState(int key, int action) {
  if(key > prevState.size()) {
    std::cout << "Input out of range" << std::endl;
    return;
  }

  if(action == GLFW_PRESS)
    prevState[key] = PRESSED;

  if(action == GLFW_RELEASE)
    prevState[key] = RELEASED;
}

void Input::updateMouse(float x, float y) {
  if(firstMove == true) {
    lastX = x;
    lastY = y;
    firstMove = false;
  }
  xPos = x;
  yPos = y;
  mouseMoved = true;
  return;
}

void Input::keyTap(int key) {
  state[key] = HOLD;
}

Input& Input::getInputs() {
  return *this;
}

std::vector<unsigned int>& Input::getStates() {
  return state;
}

std::vector<unsigned int>& Input::getPrevStates() {
  return prevState;
}
}
