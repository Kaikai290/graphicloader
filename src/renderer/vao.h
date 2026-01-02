#ifndef VAO_H
#define VAO_H

#include "vbo.h"
#include "ibo.h"

class VAO {
public:
  VAO();
  VAO(const void *verticesData, unsigned int size, const unsigned int *indicesData, unsigned int count) ;
  ~VAO();

  void bind();
  void unbind();
private:
  unsigned int vaoID;
  VBO *vboID;
  IBO *iboID;
};


#endif
