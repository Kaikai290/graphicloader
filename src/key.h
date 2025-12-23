#ifndef KEY_H
#define KEY_H

#include <vector>
#include <windows.h>

enum { 
  RELEASED, 
  PRESSED,
  HOLD 
};

class Key {
private:
  std::vector<unsigned int> state;
  std::vector<unsigned int> prevState{1024, RELEASED};

public:
  Key();
  ~Key();

  void updateState(int key, int action);
  void updatePrevState(int key, int action);

  std::vector<unsigned int>& getStates();
  std::vector<unsigned int>& getPrevStates();
};

#endif
