#pragma once

#include "../mke_core.hpp"
#include "toolbox/types.hpp"
#include "input.hpp"


namespace mkeWindow {
  inline GLFWwindow *window_id;
  extern uint32_t window_width;
  extern uint32_t window_height;


  extern void init();
  extern void closeWindow();
  extern void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
}