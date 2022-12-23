#pragma once

#include "../mke_core.hpp"
#include "toolbox/types.hpp"
#include "input.hpp"


/* Window Manager
*
* The window manager is responsible for creating the window, changing it's size with the 
* frameBufferSizeCallback, and to close the window.
*
*/


namespace mke {
  inline GLFWwindow *window_id;
  extern uint32_t window_width;
  extern uint32_t window_height;


  extern void initWindow();
  extern void closeWindow();
  extern void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
}