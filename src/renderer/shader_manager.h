#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>

struct ShaderSource{
  std::string VertexShader;
  std::string FragmentShader;
};

class ShaderManager{
public:
  unsigned int ShaderProgram;

public:
  ShaderManager(std::string VertexShaderFilePath, std::string FragmentShaderFilePath);

  void createShader(std::string VertexShaderFilePath, std::string FragmentShaderFilePath);
  void useShader();

private:
  ShaderSource LoadShadersFromFiles(std::string VertexShaderFilePath, std::string FragmentShaderFilePath);
  void GetShaderLog(unsigned int Shader, std::string ShaderType);
};

#endif // !SHADER_MANAGER_H

