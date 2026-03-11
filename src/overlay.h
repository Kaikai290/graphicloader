#ifndef OVERLAY_H
#define OVERLAY_H

#include <memory>

namespace LZ {
class Overlay {
public:
 virtual ~Overlay() = default;

  virtual void update(float deltaTime) {};
  virtual void render() {};

};
}

#endif
