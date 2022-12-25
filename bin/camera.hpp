#pragma once

#include "toolbox/types.hpp"
#include "toolbox/logger.hpp"


namespace mke {
  enum class CameraMovement {MoveUp, MoveDown, MoveLeft, MoveRight};
  struct Camera {glm::vec3 position{0}; float pitch; float yaw;};

  inline Camera mainCamera;

  extern void moveCamera(Camera &camera, CameraMovement movement);
}