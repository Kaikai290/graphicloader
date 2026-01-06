#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>

class TextureManager {
public:
  TextureManager(std::string filePath);
  ~TextureManager(); 



private:
  unsigned char* loadData(std::string filePath);
  void bindData(unsigned char* data);
  void deleteData(unsigned char* data);

  unsigned int textureID;
  int width;
  int height;
  int nrChannels;

};

#endif
