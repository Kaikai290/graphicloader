#ifndef VAO_H
#define VAO_H

#include "vbo.h"
#include "ibo.h"

#define VERTEX 0x001
#define TEXS 0x002
#define NORM 0x004
#define TEXNORM 0x006

enum VAOtype {
  NULLTYPE,
  TEX,
  TEXNOR
};

class VAO {
public:
  VAO();
  ~VAO();

  void createVAO(const void *verticesData, unsigned int size, const unsigned int *indicesData, unsigned int count, unsigned int TYPE);

  void bind();
  void unbind();
private:
  unsigned int vaoID;
  VBO *vboID;
  IBO *iboID;
  int type;
};


#endif
