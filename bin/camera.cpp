#include "camera.hpp"


namespace mke {
  void moveCamera(Camera &camera, CAMERA_MOVEMENT movement) {
    switch (movement) {
      case CAMERA_MOVEMENT::MOVE_UP:    camera.position.z -= 0.02f;
      case CAMERA_MOVEMENT::MOVE_DOWN:  camera.position.z += 0.02f;
      case CAMERA_MOVEMENT::MOVE_LEFT:  camera.position.x -= 0.02f;
      case CAMERA_MOVEMENT::MOVE_RIGHT: camera.position.x += 0.02f;
      default: print_error("Incorrect camera movement!");
    }
  }
}