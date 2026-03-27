#ifndef LAYER_H
#define LAYER_H

#include "camera.h"
#include "event.h"

#include <memory>
namespace LZ {
class Layer {
public:
 virtual ~Layer() = default;


  virtual void event(Event& event) {};
  virtual void setup(std::shared_ptr<LazyCamera> Camera) {}
  virtual void update(float deltaTime) {};
  virtual void render() {};

};
}

#endif
