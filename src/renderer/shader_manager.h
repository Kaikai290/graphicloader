#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

class ShaderManager {
public:
  unsigned int ShaderProgram;
  std::map<std::string, GLint> files;

public:
  ShaderManager();
  ShaderManager(std::string VertexShaderFilePath,
                std::string FragmentShaderFilePath);

  void createProgram();

  void createShader();

  void setVertex(std::string vertexShaderPath);
  void setFragment(std::string fragmentShaderPath);
  void setGeometry(std::string geoShaderPath);
  void setTessControl(std::string controlShaderPath);
  void setTessEval(std::string evalShaderPath);
  void setCompute(std::string computeShaderPath);

  void useShader();

  void setBool(const std::string &name, bool value) const;
  void setInt(const std::string &name, int value) const;
  void setFloat(const std::string &name, float value) const;
  void setVec2(const std::string &name, const glm::vec2 &value) const;
  void setVec2(const std::string &name, float x, float y) const;
  void setVec3(const std::string &name, const glm::vec3 &value) const;
  void setVec3(const std::string &name, float x, float y, float z) const;
  void setVec4(const std::string &name, const glm::vec4 &value) const;
  void setVec4(const std::string &name, float x, float y, float z, float w) const;
  void setMat2(const std::string &name, const glm::mat2 &mat) const;
  void setMat3(const std::string &name, const glm::mat3 &mat) const;
  void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
  void LoadShadersFromFiles();
  void convertShaders(std::string& shader, GLint type);
  void GetShaderLog(unsigned int Shader, GLint ShaderType);
};

#endif // !SHADER_MANAGER_H
