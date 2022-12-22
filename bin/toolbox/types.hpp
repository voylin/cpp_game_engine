#pragma once

// OpenGL stuff
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// std
#include <vector>

// String stuff
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

// TYPE STRING
#include <string>
#include <cstring>
typedef std::string String;

// TYPE VECTOR
typedef std::vector<GLuint>       v_GLuint;
typedef std::vector<float>        v_float;
typedef std::vector<unsigned int> v_uint;

// STRUCT VERSION
struct Version {
  unsigned int major, minor, patch;

  const String toString() const { return std::to_string(major)+'.'+std::to_string(minor)+'.'+std::to_string(patch); }
  const String toSmallString() const { return std::to_string(major)+'.'+std::to_string(minor); }
};

// STRUCT TEXTURE
struct Texture {
  GLuint textureID;
};