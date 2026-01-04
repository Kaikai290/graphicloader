#ifndef LAYER_H
#define LAYER_H

class Layer {
public:
 virtual ~Layer() = default;

  virtual void update(float deltaTime) {};
  virtual void render() {};

};

#endif
