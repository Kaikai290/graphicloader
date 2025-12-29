#ifndef LAYER_H
#define LAYER_H

class Layer {
public:
 ~Layer() = default;

  virtual void update() {};
  virtual void render() {};

};

#endif
