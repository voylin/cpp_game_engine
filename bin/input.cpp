#include "input.hpp"


namespace mke {
  void inputKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // Quick Shutdown:
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
      glfwSetWindowShouldClose(window, GLFW_TRUE);

    // Wireframe debugging:
    if (key == GLFW_KEY_X && action == GLFW_PRESS && mods == GLFW_MOD_CONTROL) {
      if (wireframe_mode) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      else glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      wireframe_mode = !wireframe_mode;
    }

    // Get FPS:
    if (key == GLFW_KEY_F && action == GLFW_PRESS && mods == GLFW_MOD_CONTROL) {
      printInfo(getFPSstring() + " FPS");
    }
  }


  void processInput() {
    // Camera controls:
    if (glfwGetKey(window_id, GLFW_KEY_W) == GLFW_PRESS) { // Move Camera up
      moveCamera(mainCamera, CameraMovement::MoveUp);
    }
    if (glfwGetKey(window_id, GLFW_KEY_S) == GLFW_PRESS) { // Move Camera Down
      moveCamera(mainCamera, CameraMovement::MoveDown);
    }
    if (glfwGetKey(window_id, GLFW_KEY_A) == GLFW_PRESS) { // Move Camera Left
      moveCamera(mainCamera, CameraMovement::MoveLeft);
    }
    if (glfwGetKey(window_id, GLFW_KEY_D) == GLFW_PRESS) { // Move Camera Right
      moveCamera(mainCamera, CameraMovement::MoveRight);
    }
  }
}