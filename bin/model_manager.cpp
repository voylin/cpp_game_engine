#include "model_manager.hpp"

// libs
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

namespace mke {
  RawModel loadToVAO(v_float positions, v_float textureCoords, v_uint indices)
  {
    GLuint vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, 3, positions);

    if (textureCoords.size() > 0) // Making the creation of raw models still possible
      storeDataInAttributeList(1, 2, textureCoords);

    unbindVAO();

    return RawModel{vaoID, static_cast<GLuint>(indices.size())};
  }

  GLuint createVAO()
  {
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID); // 1 is the amount of VAO's
    glBindVertexArray(vaoID);
    vaos.push_back(vaoID);
    return vaoID;
  }

  GLuint loadTexture(String fileName)
  {
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    // Texture wrapping parameters:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Texture filtering parameters:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load image, create texture and generate mipmaps:
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(("textures/" + fileName).c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
      if (fileName.find(".png") != String::npos)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
      throw printError("Failed to load texture '" + fileName + "'!");

    stbi_image_free(data);

    textures.push_back(texture);
    return texture;
  }

  void bindIndicesBuffer(v_uint indices)
  {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    vbos.push_back(vboID);
  }

  void storeDataInAttributeList(int attributeNr, int coordSize, v_float data)
  {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(attributeNr, coordSize, GL_FLOAT, GL_FALSE, coordSize * sizeof(float), (void *)0);
    // glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    vbos.push_back(vboID);
  }

  void unbindVAO()
  {
    glBindVertexArray(0);
  }

  void cleanUpModelManager()
  {
    if (vaos.size() != 0)
    {
      for (int i = 0; i <= vaos.size(); i++)
      {
        glDeleteVertexArrays(1, &vaos.data()[i]);
      }
    }
    if (vbos.size() != 0)
    {
      for (int i = 0; i <= vbos.size(); i++)
      {
        glDeleteBuffers(1, &vbos.data()[i]);
      }
    }
    if (textures.size() != 0)
    {
      for (int i = 0; i <= textures.size(); i++)
      {
        glDeleteTextures(1, &textures.data()[i]);
      }
    }
  }
}