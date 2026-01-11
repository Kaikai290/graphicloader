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

void VAO::createTex(const void *verticesData, unsigned int size, const unsigned int *indicesData, unsigned int count) {
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);

  vboID = new VBO(verticesData, size);
  iboID = new IBO(indicesData, count);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void *)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);

  type = TEX;
  return;
}

void VAO::createTexNor(const void *verticesData, unsigned int size, const unsigned int *indicesData, unsigned int count) {
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);

  vboID = new VBO(verticesData, size);
  iboID = new IBO(indicesData, count);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(3*sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void *)(5*sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindVertexArray(0);

  type= TEXNOR;
  return;
}

void VAO::bind() {
  glBindVertexArray(vaoID);
}


void VAO::unbind() {
  glBindVertexArray(0);
}
