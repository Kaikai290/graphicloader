#ifndef INPUT_H
#define INPUT_H

#include <vector>
#include <windows.h>

enum { RELEASED, PRESSED, HOLD };

namespace LZ {

class Input {
private:
  std::vector<unsigned int> state;
  std::vector<unsigned int> prevState{1024, RELEASED};

  float xPos, yPos, lastX, lastY;
  bool mouseMoved = false;
  bool firstMove = true;

public:
  Input();
  ~Input();

  void updateState(int key, int action);
  void updatePrevState(int key, int action);
  void keyTap(int key);

  void updateMouse(float x, float y);
  inline void movedMouse() { mouseMoved = false; }

  inline bool ifMouseMove() const { return mouseMoved; }
  inline float xOffset() {
    float offset = xPos - lastX;
    lastX = xPos;
    return offset;
  }
  inline float yOffset() {
    float offset = lastY - yPos;
    lastY = yPos;
    return offset;
  }

  Input &getInputs();
  std::vector<unsigned int> &getStates();
  std::vector<unsigned int> &getPrevStates();
};
} // namespace LZ
#endif
