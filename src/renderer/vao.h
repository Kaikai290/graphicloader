#ifndef VAO_H
#define VAO_H

#include "vbo.h"
#include "ibo.h"

enum VAOtype {
  NULLTYPE,
  TEX,
  TEXNOR
};

class VAO {
public:
  VAO();
  ~VAO();

  void createTex(const void *verticesData, unsigned int size, const unsigned int *indicesData, unsigned int count);

  void createTexNor(const void *verticesData, unsigned int size, const unsigned int *indicesData, unsigned int count);

  void bind();
  void unbind();
private:
  unsigned int vaoID;
  VBO *vboID;
  IBO *iboID;
  int type;
};


#endif
