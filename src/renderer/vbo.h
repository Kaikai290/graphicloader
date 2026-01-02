#ifndef VBO_H
#define VBO_H

class VBO {
public:
  VBO(const void* data, unsigned int size);
  ~VBO();

  void bind();
  void unbind();

private:
  unsigned int vboID;
};

#endif
