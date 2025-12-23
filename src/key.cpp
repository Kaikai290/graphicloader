#include <GLFW/glfw3.h>
#include <iostream>

#include "key.h"

Key::Key() : state(1024, RELEASED), prevState(1024, RELEASED){};

Key::~Key() {};

void Key::updateState(int key, int action) {
  if(key > state.size()) {
    std::cout << "Key out of range" << std::endl;
    return;
  }

  if(action == GLFW_PRESS) {
    state[key] = PRESSED;
  }

  if(action == GLFW_RELEASE) {
    state[key] = RELEASED;
  }
}

void Key::updatePrevState(int key, int action) {
  if(key > prevState.size()) {
    std::cout << "Key out of range" << std::endl;
    return;
  }

  if(action == GLFW_PRESS)
    prevState[key] = PRESSED;

  if(action == GLFW_RELEASE)
    prevState[key] = RELEASED;
}

std::vector<unsigned int>& Key::getStates() {
  return state;
}

std::vector<unsigned int>& Key::getPrevStates() {
  return prevState;
}
