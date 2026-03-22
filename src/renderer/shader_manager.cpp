#include "shader_manager.h"
#include "log.h"
#include <fstream>

ShaderManager::ShaderManager() { createProgram(); }

ShaderManager::ShaderManager(std::string VertexShaderFilePath,
                             std::string FragmentShaderFilePath) {
  this->createProgram();
  setVertex(VertexShaderFilePath);
  setFragment(FragmentShaderFilePath);
  this->createShader();
}

void ShaderManager::createProgram() { ShaderProgram = glCreateProgram(); }

void ShaderManager::setVertex(std::string vertexShaderPath) {
 files[vertexShaderPath]  = GL_VERTEX_SHADER;
}

void ShaderManager::setFragment(std::string fragmentShaderPath) {
 files[fragmentShaderPath]  = GL_FRAGMENT_SHADER; 
}

void ShaderManager::setGeometry(std::string geoShaderPath) {
 files[geoShaderPath]  = GL_GEOMETRY_SHADER; 
}

void ShaderManager::setTessControl(std::string controlShaderPath) {
  files[controlShaderPath] = GL_TESS_CONTROL_SHADER;
}

void ShaderManager::setTessEval(std::string evalShaderPath) {
  files[evalShaderPath] = GL_TESS_EVALUATION_SHADER;
}

void ShaderManager::setCompute(std::string computeShaderPath) {
 files[computeShaderPath]  = GL_COMPUTE_SHADER;
}

void ShaderManager::LoadShadersFromFiles() {
  for(auto shader: files) {
    LZ::Log::printInfo("Creating Shader: ", shader.first); 
    std::ifstream workingShader(shader.first);
    if(!workingShader.is_open()) {
      std::cout << "Shader failed to open with ID: " << shader.second << std::endl;
    }
    std::stringstream workingShaderStream;
    workingShaderStream << workingShader.rdbuf();
    std::string finishedShader = workingShaderStream.str();

    convertShaders(finishedShader, shader.second);

    workingShader.close();
  } glLinkProgram(ShaderProgram);

  GetShaderLog(ShaderProgram, GL_LINK_STATUS);
}

void ShaderManager::createShader() {
  LoadShadersFromFiles();
}

void ShaderManager::convertShaders(std::string &shaderString, GLint type) {
  unsigned int shader = glCreateShader(type);

  const char *shaderPointer = shaderString.c_str();
  glShaderSource(shader, 1, &shaderPointer, NULL);
  glCompileShader(shader);

  GetShaderLog(shader, type);

  glAttachShader(ShaderProgram, shader);
  glDeleteShader(shader);
}

void ShaderManager::useShader() { glUseProgram(ShaderProgram); }

void ShaderManager::GetShaderLog(unsigned int Shader, GLint ShaderType) {
  int success;

  std::string log;
  GLint logLength;

  glGetShaderiv(Shader, GL_INFO_LOG_LENGTH, &logLength);

  if (ShaderType == GL_LINK_STATUS) {
    glGetProgramiv(Shader, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(Shader, logLength, NULL, log.data());
      std::cout << "ERROR::SHADER::LINKING::COMPILATION_FAILED\n"
                << log.c_str() << std::endl;
      return;
    }
  } else {
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(Shader, logLength, NULL, log.data());
      std::cout << "ERROR::SHADER::" << ShaderType << "::COMPILATION_FAILED\n"
                << log.c_str() << std::endl;
    }
  }
  return;
}

void ShaderManager::setBool(const std::string &name, bool value) const {
  glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), (int)value);
}

void ShaderManager::setInt(const std::string &name, int value) const {
  glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), value);
}

void ShaderManager::setFloat(const std::string &name, float value) const {
  glUniform1f(glGetUniformLocation(ShaderProgram, name.c_str()), value);
}

void ShaderManager::setVec2(const std::string &name,
                            const glm::vec2 &value) const {
  glUniform2fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, &value[0]);
}

void ShaderManager::setVec2(const std::string &name, float x, float y) const {
  glUniform2f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y);
}

void ShaderManager::setVec3(const std::string &name,
                            const glm::vec3 &value) const {
  glUniform3fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, &value[0]);
}

void ShaderManager::setVec3(const std::string &name, float x, float y,
                            float z) const {
  glUniform3f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y, z);
}

void ShaderManager::setVec4(const std::string &name,
                            const glm::vec4 &value) const {
  glUniform4fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1, &value[0]);
}

void ShaderManager::setVec4(const std::string &name, float x, float y, float z,
                            float w) const {
  glUniform4f(glGetUniformLocation(ShaderProgram, name.c_str()), x, y, z, w);
}

void ShaderManager::setMat2(const std::string &name,
                            const glm::mat2 &mat) const {
  glUniformMatrix2fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1,
                     GL_FALSE, &mat[0][0]);
}

void ShaderManager::setMat3(const std::string &name,
                            const glm::mat3 &mat) const {
  glUniformMatrix3fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1,
                     GL_FALSE, &mat[0][0]);
}

void ShaderManager::setMat4(const std::string &name,
                            const glm::mat4 &mat) const {
  glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, name.c_str()), 1,
                     GL_FALSE, &mat[0][0]);
}
