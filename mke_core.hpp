#pragma once
#include "bin/toolbox/logger.hpp"
#include "bin/window_manager.hpp"
#include "bin/camera.hpp"
#include "bin/input.hpp"
#include "bin/model_manager.hpp"
#include "bin/renderer.hpp"
#include "bin/toolbox/time_manager.hpp"
#include "bin/shaders/shader_program.hpp"


namespace mkeCore {
  static const String ENGINE_NAME = "Meikyuu Engine";
  static const Version ENGINE_VERSION{0,1,0};
  static const Version OPEN_GL_VERSION{4,5};
  inline const String *GAME_NAME;
  inline const Version *GAME_VERSION;


  void startEngine(const String *game_name, const Version *game_version);
  void run();
  void shutdownEngine();
}