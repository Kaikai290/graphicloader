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
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);

  vboID = new VBO(triangleVertices, sizeof(triangleVertices));

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(0);
  return;
};

VAO::VAO(const void *verticesData, unsigned int size, const unsigned int *indicesData, unsigned int count) {
  glGenVertexArrays(1, &vaoID);
  glBindVertexArray(vaoID);

  vboID = new VBO(verticesData, size);
  iboID = new IBO(indicesData, count);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void *)(3*sizeof(float)));
  glEnableVertexAttribArray(1);

  glBindVertexArray(0);
  return;

}

VAO::~VAO() {
  delete vboID;
  delete iboID;
  glDeleteVertexArrays(1, &vaoID);
}

void VAO::bind() {
  glBindVertexArray(vaoID);
}


void VAO::unbind() {
  glBindVertexArray(0);
}
