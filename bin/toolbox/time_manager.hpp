#pragma once

#include "types.hpp"


namespace mke {
  static float timeStarted;
  static float beginTime;
  static float endTime;
  static float delta = -1.0f;


  inline void initTime() {
    timeStarted = static_cast<float>(glfwGetTime());
  }


  inline float getRunTime() {
    return (static_cast<float>(glfwGetTime()) - timeStarted);
  }


  inline void setDeltaStartTimes() {
    beginTime = glfwGetTime();
    endTime = glfwGetTime();
  }


  inline void setDeltaTimes() {
    endTime = glfwGetTime();
    delta = endTime - beginTime;
    beginTime = endTime;
  }

  // Possibly not working correctly
  // If time is in miliseconds than: 1000/ delta
  // TODO: Check this
  inline float getFPS() { return 1.0f / delta; }
  inline String getFPSstring() { return std::to_string(1.0f / delta); }
}