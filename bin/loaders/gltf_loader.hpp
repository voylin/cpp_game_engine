#pragma once

#include "../toolbox/types.hpp"
#include "../toolbox/logger.hpp"
#include "../toolbox/json.hpp"
#include "../toolbox/file_reader.hpp"
#include "../model_manager.hpp"


namespace mke {
  extern Model loadGLTF(const String &filename);

  extern v_float _getFloatsGLTF(const dic_JsonValue &data, v_uchar &binData, const JsonValue &accessor);
  extern v_GLuint _getIndicesGLTF(const JsonValue &accessor);

  extern v_vec2 _groupFloatsVec2GLTF(const v_float floatVec);
  extern v_vec3 _groupFloatsVec3GLTF(const v_float floatVec);
  extern v_vec4 _groupFloatsVec4GLTF(const v_float floatVec);

  extern v_Vertex _assembleVertices(v_vec3 positions, v_vec3 normals, v_vec2 texUVs);
}