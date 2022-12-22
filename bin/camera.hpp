#pragma once

#include "toolbox/types.hpp"
#include "toolbox/logger.hpp"


namespace mkeCamera {
  enum CAMERA_MOVEMENT {MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT};
  struct Camera {glm::vec3 position{0}; float pitch; float yaw;};

  inline Camera mainCamera;

  extern void moveCamera(Camera &camera, CAMERA_MOVEMENT movement);
}