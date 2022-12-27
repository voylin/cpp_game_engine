#pragma once

// OpenGL stuff
#include "../include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// std
#include <vector>
#include <unordered_map>

// String stuff
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

// String
#include <string>
#include <cstring>
typedef std::string String;

struct Vertex;
struct TexCoord;
struct Texture;
struct JsonValue;

// TYPE VECTOR
typedef std::vector<GLuint>        v_GLuint;
typedef std::vector<float>         v_float;
typedef std::vector<int>           v_int;
typedef std::vector<unsigned int>  v_uint;
typedef std::vector<unsigned char> v_uchar;
typedef std::vector<Vertex>        v_Vertex;
typedef std::vector<TexCoord>      v_TexCoord;
typedef std::vector<JsonValue>     v_JsonValue;
typedef std::vector<glm::vec3>     v_vec3;
typedef std::vector<glm::quat>     v_quat;
typedef std::vector<glm::mat4>     v_mat4;

// TYPE DIC
typedef std::unordered_map<String, JsonValue>   dic_JsonValue;


// Structs:
enum class JsonType { Number, String, Bool, Null, Array, Object };
struct JsonValue {
  JsonType type;
  String stringValue;
  double numValue;
  bool boolValue;
  v_JsonValue arrayValue;
  dic_JsonValue objectValue;
};


struct Version {
  unsigned int major, minor, patch;

  const String toString() const { return std::to_string(major)+'.'+std::to_string(minor)+'.'+std::to_string(patch); }
  const String toSmallString() const { return std::to_string(major)+'.'+std::to_string(minor); }
};

struct Vertex { float x, y, z; };
struct TexCoord { float u, v; };
struct Texture { GLuint textureID; };