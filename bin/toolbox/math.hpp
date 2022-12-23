#pragma once

#include "types.hpp"
#include "../renderer.hpp"
#include "../shaders/shaders.hpp"
#include "../shaders/shader_program.hpp"
#include "../camera.hpp"


namespace mke {
  glm::mat4 createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale);
  glm::mat4 createViewMatrix(Camera camera);
  void createProjectionMatrix(StaticShader shader);
}