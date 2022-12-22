#pragma once

#include "toolbox/types.hpp"
#include "toolbox/logger.hpp"

#include "models.hpp"


namespace mkeModelManager {
  // These are vectors (v_*type*)
  inline v_GLuint vaos;
  inline v_GLuint vbos;
  inline v_GLuint textures;
  

  extern RawModel loadToVAO(v_float positions, v_float textureCoords, v_uint indices);
  extern GLuint createVAO();
  
  extern GLuint loadTexture(String fileName);
  extern void bindIndicesBuffer(v_uint indices);
  extern void storeDataInAttributeList(int attributeNr, int coordSize, v_float data);

  extern void unbindVAO();
  extern void cleanUp();
}