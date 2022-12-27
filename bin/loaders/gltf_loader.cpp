#include "gltf_loader.hpp"

namespace mke {
  Model loadGLTF(const String &filename) {
    JsonValue data = parseJsonFile(filename);
    
    // Getting the data
    
    String uri = getJsonString(getJsonArray(data, "buffers")[0], "uri");
    String bytesText = getFileBinData("models/" + uri);
    v_uchar binData(bytesText.begin(), bytesText.end());


    return Model{};
  }


  v_float _getFloatsGLTF(dic_JsonValue &data, v_uchar &binData, dic_JsonValue &accessor) {
    v_float floatVec;

    uint buffViewInd = (accessor.find("bufferView") != accessor.end()) ? static_cast<uint>(accessor["bufferView"].numValue) : 1;
    uint count = static_cast<uint>(accessor["count"].numValue);
    uint accByteOffset = (accessor.find("byteOffset") != accessor.end()) ? static_cast<uint>(accessor["byteOffset"].numValue) : 0;
    String type = accessor["type"].stringValue;

    JsonValue bufferView = data["bufferViews"].objectValue["buffViewInd"];
    uint byteOffset = static_cast<uint>(bufferView.objectValue["byteOffset"].numValue);

    uint numPerVert;
    if (type == "SCALAR") numPerVert = 1;
    else if (type == "VEC2") numPerVert = 2;
    else if (type == "VEC3") numPerVert = 3;
    else if (type == "VEC4") numPerVert = 4;
    else throw printError("Type is invalid (not SCALAR, VEC2, VEC3, or VEC4)!");

    uint beginningOfData = byteOffset + accByteOffset;
    uint lengthOfData = count * 4 * numPerVert;
    for (uint i = beginningOfData; i < beginningOfData + lengthOfData; i) {
      uchar bytes[] = { binData[i++], binData[i++], binData[i++], binData[i++] };
      float value;
      std::memcpy(&value, bytes, sizeof(float));
      floatVec.push_back(value);
    }
    
    return floatVec;
  }


  v_GLuint _getIndicesGLTF(dic_JsonValue &data, v_uchar &binData, dic_JsonValue &accessor) {
    v_GLuint indices;

    uint buffViewInd = (accessor.find("bufferView") != accessor.end()) ? static_cast<uint>(accessor["bufferView"].numValue) : 1;
    uint count = static_cast<uint>(accessor["count"].numValue);
    uint accByteOffset = (accessor.find("byteOffset") != accessor.end()) ? static_cast<uint>(accessor["byteOffset"].numValue) : 0;
    uint componentType = static_cast<uint>(accessor["componentType"].numValue);

    JsonValue bufferView = data["bufferViews"].objectValue["buffViewInd"];
    uint byteOffset = static_cast<uint>(bufferView.objectValue["byteOffset"].numValue);

    uint beginningOfData = byteOffset + accByteOffset;
    if (componentType == 5125) { // Unsigned int
      for (uint i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i) {
        uchar bytes[] = { binData[i++], binData[i++], binData[i++], binData[i++] };
        uint value;
        std::memcpy(&value, bytes, sizeof(uint));
        indices.push_back((GLuint)value);
      }
    } else if (componentType == 5123) { // Unsigned short
      for (uint i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i) {
        uchar bytes[] = { binData[i++], binData[i++] };
        uint value;
        std::memcpy(&value, bytes, sizeof(ushort));
        indices.push_back((GLuint)value);
      }
    } else if (componentType == 5122) { // Short
      for (uint i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i) {
        uchar bytes[] = { binData[i++], binData[i++] };
        uint value;
        std::memcpy(&value, bytes, sizeof(short));
        indices.push_back((GLuint)value);
      }
    }

    return indices;
  }


  v_vec2 _groupFloatsVec2GLTF(const v_float floatVec) {
    v_vec2 vectors;
    for (int i = 0; i < floatVec.size(); i) 
      vectors.push_back(glm::vec2(floatVec[i++], floatVec[i++]));
    return vectors;
  }


  v_vec3 _groupFloatsVec3GLTF(const v_float floatVec) {
    v_vec3 vectors;
    for (int i = 0; i < floatVec.size(); i) 
      vectors.push_back(glm::vec3(floatVec[i++], floatVec[i++], floatVec[i++]));
    return vectors;
  }


  v_vec4 _groupFloatsVec4GLTF(const v_float floatVec) {
    v_vec4 vectors;
    for (int i = 0; i < floatVec.size(); i) 
      vectors.push_back(glm::vec4(floatVec[i++], floatVec[i++], floatVec[i++], floatVec[i++]));
    return vectors;
  }


  v_Vertex _assembleVertices(v_vec3 positions, v_vec3 normals, v_vec2 texUVs) {
    v_Vertex vertices;
    for (int i = 0; i < positions.size(); i++) {
      vertices.push_back(
        Vertex{
          positions[i],
          normals[i],
          glm::vec3(1.0f, 1.0f, 1.0f),
          texUVs[i]
        }
      );
      Many things are going against me with this gltf stuff so I'm putting a stop to my suffering for now ^^"
    }
    return vertices;
  }

}