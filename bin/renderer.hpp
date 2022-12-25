#pragma once

#include "window_manager.hpp"
#include "toolbox/types.hpp"
#include "toolbox/logger.hpp"
#include "nodes/node3D.hpp"
#include "shaders/shader_program.hpp"
#include "toolbox/math.hpp"


namespace mke {
  inline glm::mat4 projectionMatrix;


  extern void prepareRenderer();
 
  extern void render(Node3D node);
}