#pragma once

#include "window_manager.hpp"
#include "toolbox/types.hpp"
#include "toolbox/logger.hpp"
#include "nodes/node3D.hpp"
#include "shaders/shader_program.hpp"
#include "toolbox/math.hpp"


namespace mkeRenderer {
  static const float FOV = 70.0f;
  static const float NEAR_PLANE = 0.1f;
  static const float FAR_PLANE = 1000.0f;

  inline glm::mat4 projectionMatrix;


  extern void prepare();
 
  extern void render(RawModel model);
  extern void render(TexturedModel texturedModel);
  extern void render(mkeNode3D::Node3D node, mkeShaderProgram::StaticShader shader);

  extern void createProjectionMatrix(mkeShaderProgram::StaticShader shader);
}