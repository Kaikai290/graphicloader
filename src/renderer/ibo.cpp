#include "ibo.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>


IBO::IBO(const unsigned int *data, unsigned int count) {
  glGenBuffers(1, &iboID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(unsigned int), data, GL_STATIC_DRAW);
}


void IBO::bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
}

void IBO::unbind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
}
