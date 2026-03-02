#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "vao.h"

float triangleVertices[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };

VAO::VAO() {
};

VAO::~VAO() {
  if(type == NULLTYPE)
    return;

  delete vboID;
  delete iboID;
  glDeleteVertexArrays(1, &vaoID);
}

void VAO::createVAO(const void *verticesData, unsigned int size, const unsigned int *indicesData, unsigned int count, unsigned int TYPE) {
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);

  vboID = new VBO(verticesData, size);

  if(indicesData != nullptr)
    iboID = new IBO(indicesData, count);

  unsigned int spacer = 0;
  unsigned int offset = 0;

  switch(TYPE) {
    case VERTEX: 
      spacer = 3;
      break;
    case TEXS:
      spacer = 5;
      break;
    case NORM:
      spacer = 6;
      break;
    case TEXNORM:
      spacer = 8;
      break;
  }

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, spacer*sizeof(float), (void *)offset);
  glEnableVertexAttribArray(0);

  offset += 3;

  if(TYPE & TEXS) {
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, spacer*sizeof(float), (void *)(offset*sizeof(float)));
    glEnableVertexAttribArray(1);
    offset += 2;
  }

  if(TYPE & NORM) {
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, spacer*sizeof(float), (void *)(offset*sizeof(float)));
    glEnableVertexAttribArray(2);
    offset += 3;
  }

  glBindVertexArray(0);

  type = TYPE;
  return;
}


void VAO::bind() {
  glBindVertexArray(vaoID);
}


void VAO::unbind() {
  glBindVertexArray(0);
}
