#pragma once

#include "toolbox/types.hpp"


struct RawModel {
    GLuint vaoID;
    GLuint vertexCount;
};

struct TexturedModel {
  RawModel rawModel;
  Texture texture;
};
