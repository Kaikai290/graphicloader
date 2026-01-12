#include "texture_manager.h"

#include "../log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

TextureManager::TextureManager() {}


TextureManager::TextureManager(std::string filePath) {
  stbi_set_flip_vertically_on_load(true);
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 7); // pick mipmap level 7 or lower


  unsigned char* data = loadData(filePath);
  if(!data) {
    Log::printError("Failed to load texture");
    return;
  }
  bindData(data);
  deleteData(data);
}

TextureManager::~TextureManager() {}

unsigned char* TextureManager::loadData(std::string filePath){
  unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
  return data;
}

void TextureManager::bindData(unsigned char *data) {
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); 
  glGenerateMipmap(GL_TEXTURE_2D);
}

void TextureManager::deleteData(unsigned char *data) {
  stbi_image_free(data);
}
