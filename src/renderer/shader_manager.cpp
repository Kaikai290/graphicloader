#include "shader_manager.h"

ShaderManager::ShaderManager(std::string VertexShaderFilePath,
                             std::string FragmentShaderFilePath) {
  ShaderProgram = glCreateProgram();
  this->createShader(VertexShaderFilePath, FragmentShaderFilePath);
}

ShaderSource
ShaderManager::LoadShadersFromFiles(std::string VertexShaderFilePath,
                                    std::string FragmentShaderFilePath) {
  ShaderSource CurrentShader;

  std::ifstream VertexShader(VertexShaderFilePath);
  if (!VertexShader.is_open()) {
    std::cout << "Vertex Shader failed to open file" << std::endl;
  }

  std::ifstream FragmentShader(FragmentShaderFilePath);
  if (!FragmentShader.is_open()) {
    std::cout << "Fragment Shader failed to open file" << std::endl;
  }

  std::stringstream VertexShaderStream;
  VertexShaderStream << VertexShader.rdbuf();
  CurrentShader.VertexShader = VertexShaderStream.str();

  VertexShader.close();

  std::stringstream FragmentShaderStream;
  FragmentShaderStream << FragmentShader.rdbuf();
  CurrentShader.FragmentShader = FragmentShaderStream.str();

  FragmentShader.close();

  return CurrentShader;
}

void ShaderManager::createShader(std::string VertexShaderFilePath,
                                 std::string FragmentShaderFilePath) {
  ShaderSource ShaderFiles = LoadShadersFromFiles(
      VertexShaderFilePath,
      FragmentShaderFilePath); // Change this from absolute paths

  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

  const char *VertexShaderPointer = ShaderFiles.VertexShader.c_str();
  glShaderSource(vertexShader, 1, &VertexShaderPointer, NULL);
  glCompileShader(vertexShader);

  GetShaderLog(vertexShader, "VERTEX");

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

  const char *FragmentShaderPointer = ShaderFiles.FragmentShader.c_str();
  glShaderSource(fragmentShader, 1, &FragmentShaderPointer, NULL);
  glCompileShader(fragmentShader);

  GetShaderLog(fragmentShader, "FRAGMENT");

  glAttachShader(ShaderProgram, vertexShader);
  glAttachShader(ShaderProgram, fragmentShader);
  glLinkProgram(ShaderProgram);

  GetShaderLog(ShaderProgram, "LINKING");

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
}

void ShaderManager::useShader() { glUseProgram(ShaderProgram); }

void ShaderManager::GetShaderLog(unsigned int Shader, std::string ShaderType) {
  int success;
  char infoLog[1024*4];
  if (ShaderType == "LINKING") {
    glGetShaderiv(Shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(Shader, 1024*4, NULL, infoLog);
      std::cout << "ERROR::SHADER::" << ShaderType << "::COMPILATION_FAILED\n"
                << infoLog << std::endl;
    }
  }
  else {
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(Shader, 1024*4, NULL, infoLog);
      std::cout << "ERROR::SHADER::" << ShaderType << "::COMPILATION_FAILED\n"
                << infoLog << std::endl;
    }
  }
}
