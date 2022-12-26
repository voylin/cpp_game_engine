#include "model_manager.hpp"

// libs
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"

namespace mke {
  Model loadToVAO(v_Vertex vertices, v_TexCoord textureCoords, v_uint indices) {
    GLuint vaoID = createVAO();
    bindIndicesBuffer(indices);
    storeDataInAttributeList(0, 3, vertices);

    if (textureCoords.size() > 0) // Making the creation of raw models still possible
      storeDataInAttributeList(1, 2, textureCoords);

    unbindVAO();

    return Model{vaoID, static_cast<GLuint>(indices.size())};
  }


  Model loadToVAO(v_Vertex vertices, v_TexCoord textureCoords, v_uint indices, Texture texture) {
    Model model = loadToVAO(vertices, textureCoords, indices);
    model.texture = texture;
    return model;
  }


  GLuint createVAO() {
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID); // 1 is the amount of VAO's
    glBindVertexArray(vaoID);
    vaos.push_back(vaoID);
    return vaoID;
  }


  GLuint loadTexture(String fileName) {
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
    if (data) {
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


  void bindIndicesBuffer(v_uint indices) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    vbos.push_back(vboID);
  }


  template <typename T>
  void storeDataInAttributeList(int attributeNr, int coordSize, T& data) {
    GLuint vboID;
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);

    // Check if T is a Vertex or TexCoord struct
    if constexpr (std::is_same_v<T, v_Vertex>) {
      glVertexAttribPointer(attributeNr, coordSize, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, x));
      glVertexAttribPointer(attributeNr + 1, coordSize, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, y));
      glVertexAttribPointer(attributeNr + 2, coordSize, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, z));
    }
    else if constexpr (std::is_same_v<T, v_TexCoord>) {
      glVertexAttribPointer(attributeNr, coordSize, GL_FLOAT, GL_FALSE, sizeof(TexCoord), (void *)offsetof(TexCoord, u));
      glVertexAttribPointer(attributeNr + 1, coordSize, GL_FLOAT, GL_FALSE, sizeof(TexCoord), (void *)offsetof(TexCoord, v));
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    vbos.push_back(vboID);
  }


  void unbindVAO() { glBindVertexArray(0); }


  void cleanUpModelManager() {
    if (vaos.size() != 0) {
      for (int i = 0; i <= vaos.size(); i++) { glDeleteVertexArrays(1, &vaos.data()[i]); }
    }
    if (vbos.size() != 0) {
      for (int i = 0; i <= vbos.size(); i++) { glDeleteBuffers(1, &vbos.data()[i]); }
    }
    if (textures.size() != 0) {
      for (int i = 0; i <= textures.size(); i++) { glDeleteTextures(1, &textures.data()[i]); }
    }
  }
}