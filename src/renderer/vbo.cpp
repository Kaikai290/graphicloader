#include "vbo.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

VBO::VBO(const void *data, unsigned int size) {
  glGenBuffers(1, &vboID);
  glBindBuffer(GL_ARRAY_BUFFER, vboID);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

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
