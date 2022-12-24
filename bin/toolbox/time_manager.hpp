#pragma once

#include "types.hpp"

#include <mutex>
#include <chrono>
using std::chrono::high_resolution_clock;


namespace mke {
  inline static std::mutex mutexTimeManager;
  inline std::chrono::time_point<high_resolution_clock> timeStarted, beginTime, endTime;
  inline double delta;

  inline void initTime() { timeStarted = high_resolution_clock::now(); }

  inline double getRunTime() {
    return std::chrono::duration_cast<std::chrono::duration<double>>(
      high_resolution_clock::now() - timeStarted).count();
  }


  inline void setDeltaStartTimes() {
    beginTime = high_resolution_clock::now();
    endTime = high_resolution_clock::now();
  }


  inline void setDeltaTimes() {
    endTime = std::chrono::high_resolution_clock::now();
    std::lock_guard<std::mutex> lock(mutexTimeManager);
    delta = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - beginTime).count();
    beginTime = endTime;
  }

  inline double getFPS() {
    std::lock_guard<std::mutex> lock(mutexTimeManager);
    return 1.0 / delta;
  }
  inline String getFPSstring(bool rounded = true) { 
    if (!rounded) return std::to_string(getFPS());
    return std::to_string(std::round(static_cast<float>(getFPS()) * 100.0) / 100.0);
  }
}