#pragma once

#include "toolbox/types.hpp"
#include "toolbox/logger.hpp"

#include "models.hpp"


namespace mke {
  static v_GLuint vaos;
  static v_GLuint vbos;
  static v_GLuint textures;
  

  extern Model loadToVAO(v_float positions, v_float textureCoords, v_uint indices);
  extern Model loadToVAO(v_float positions, v_float textureCoords, v_uint indices, Texture texture);
  extern GLuint createVAO();
  
  extern GLuint loadTexture(String fileName);
  extern void bindIndicesBuffer(v_uint indices);
  extern void storeDataInAttributeList(int attributeNr, int coordSize, v_float data);

  extern void unbindVAO();
  extern void cleanUpModelManager();
}