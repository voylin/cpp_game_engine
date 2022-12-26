#include "obj_loader.hpp"

namespace mke {
  Model loadOBJ(const String obj_name) {
    v_Vertex vertices;
    v_TexCoord texCoords;
    v_uint indices;

    String line;
    std::ifstream obj_file("models/" + obj_name);
    if (obj_file.is_open()) {
      while (std::getline(obj_file, line)) {
        std::stringstream ss(line);
        String type;
        ss >> type;
        
        if (type == "v") { // Vertex data
          Vertex vertex;
          ss >> vertex.x >> vertex.y >> vertex.z;
          vertices.push_back(vertex);
        } 
        else if (type == "vt") { // Texture coordinate data
          TexCoord texCoord;
          ss >> texCoord.u >> texCoord.v;
          texCoords.push_back(texCoord);
        } 
        else if (type == "f") { // Face data
          int v1, v2, v3;
          int t1, t2, t3;
          char slash;
          ss >> v1 >> slash >> t1 >> v2 >> slash >> t2 >> v3 >> slash >> t3;
          // Indices in OBJ files start at 1, so we need to subtract 1 to get the correct index in our arrays
          indices.push_back(v1 - 1);
          indices.push_back(v2 - 1);
          indices.push_back(v3 - 1);
        }
      }

      obj_file.close();
    }
    return loadToVAO(vertices, texCoords, indices);
  }
}