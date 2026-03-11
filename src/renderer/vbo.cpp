#include "vbo.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

VBO::VBO(const void *data, unsigned int size) {
  glCreateBuffers(1, &vboID);
  //glGenBuffers(1, &vboID);
  glNamedBufferStorage(vboID, size, data, GL_MAP_READ_BIT);
  //glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);

  return;
}

VBO::~VBO() {
  glDeleteBuffers(1, &vboID);
}

void VBO::bind() {
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
}

void VBO::unbind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
