#pragma once

#include "shaders.hpp"

#include "../camera.hpp"

#include "../toolbox/types.hpp"
#include "../toolbox/logger.hpp"
#include "../toolbox/math.hpp"


namespace mke {
  static const String SIMPLE_VERT_FILE = "simple_shader.vert";
  static const String SIMPLE_FRAG_FILE = "simple_shader.frag";

  inline StaticShader staticShader;


  ShaderProgram createShaderProgram(String vertexFile, String fragmentFile);
  void createStaticShader();
  
  void startShaderProgram(ShaderProgram program);
  void stopShaderProgram();

  void bindAttribute(ShaderProgram program, int attribute, String variableName);
  GLuint getUniformLocation(ShaderProgram program, String uniformName);

  void bindAttributes(ShaderProgram program);

  void cleanUpShaderProgram(ShaderProgram program);

  void loadBool(GLuint location, bool value);
  void loadFloat(GLuint location, float value);
  void loadVector(GLuint location, glm::vec3 vector);
  void loadVector(GLuint location, float vectorX, float vectorY, float vectorZ);
  void loadMatrix(GLuint location, glm::mat4 matrix); // We may need to use pointers for these loaders ...
  
  void loadTransformationMatrix(StaticShader program, glm::mat4 matrix);
  void loadProjectionMatrix(StaticShader program, glm::mat4 matrix);
  void loadViewMatrix(StaticShader shader, Camera camera);

  GLuint loadShader(String filePath, int type);
}