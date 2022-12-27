#pragma once

#include "../toolbox/types.hpp"
#include "../toolbox/logger.hpp"
#include "../toolbox/json.hpp"
#include "../model_manager.hpp"


namespace mke {
  extern Model loadGLTF(const String &filename);
}