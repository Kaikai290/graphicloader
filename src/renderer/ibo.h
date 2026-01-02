#ifndef IBO_H
#define IBO_H

class IBO {
public:
  IBO(); // sort this out
  IBO(const unsigned int *data, unsigned int count);

  void bind();
  void unbind();

private:
  unsigned int iboID;
};

#endif
