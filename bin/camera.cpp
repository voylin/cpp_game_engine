#include "camera.hpp"


namespace mke {
  void moveCamera(Camera &camera, CameraMovement movement) {
    switch (movement) {
      case CameraMovement::MoveUp:    camera.position.z -= 0.02f;
      case CameraMovement::MoveDown:  camera.position.z += 0.02f;
      case CameraMovement::MoveLeft:  camera.position.x -= 0.02f;
      case CameraMovement::MoveRight: camera.position.x += 0.02f;
      default: printError("Incorrect camera movement!");
    }
  }
}