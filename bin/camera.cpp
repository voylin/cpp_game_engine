#include "camera.hpp"


namespace mke {
  void moveCamera(Camera &camera, CameraMovement movement) {
    switch (movement) {
      case CameraMovement::MoveUp:
        camera.position.z -= 0.02f;
        break;
      case CameraMovement::MoveDown:  
        camera.position.z += 0.02f;
        break;
      case CameraMovement::MoveLeft:  
        camera.position.x -= 0.02f;
        break;
      case CameraMovement::MoveRight: 
        camera.position.x += 0.02f;
        break;
      default: printError("Incorrect camera movement!");
    }
  }
}