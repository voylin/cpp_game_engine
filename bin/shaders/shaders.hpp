#pragma once 

#include "../toolbox/types.hpp"

struct ShaderProgram {
  GLuint programID;
  GLuint vertexShaderID;
  GLuint fragmentShaderID;
};


struct StaticShader {
  ShaderProgram shaderProgram;
  GLuint location_transformationMatrix;
  GLuint location_projectionMatrix;
  GLuint location_viewMatrix;
};