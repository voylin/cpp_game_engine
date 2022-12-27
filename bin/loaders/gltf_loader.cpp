#include "gltf_loader.hpp"

namespace mke {
  Model loadGLTF(const String &filename) {
    JsonValue data = parseJsonFile(filename);

    v_JsonValue meshes = getJsonArray(data, "meshes");
    for (const JsonValue &mesh : meshes) {
      I got until this point, typing this in normal characters so it gives an error,
      this way I know where I left of :p
    }

    return Model{};
  }
}