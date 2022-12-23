#pragma once

#include "../mke_core.hpp"
#include "camera.hpp"
#include "toolbox/types.hpp"
#include "window_manager.hpp"
#include "toolbox/time_manager.hpp"

namespace mke {
  static bool wireframe_mode = false; // true = line, false = fill


  extern void inputKeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
  extern void processInput(); // For movement controls
}