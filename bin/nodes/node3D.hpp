#pragma once

#include "../toolbox/types.hpp"
#include "../model_manager.hpp"


namespace mke {
  struct Node3D {
    Model model;
    glm::vec3 position{0};
    glm::vec3 rotation{0};
    float scale = 1;
  };


  inline Node3D createNode3D(Model model, glm::vec3 position, glm::vec3 rotation, float scale) {
    return Node3D{model, position, rotation, scale};
  }


  inline void node3DIncreasePosition(Node3D &node, float dx, float dy, float dz) {
    node.position.x += dx;
    node.position.y += dy;
    node.position.z += dz;
  }


  inline void node3DIncreasePosition(Node3D &node, glm::vec3 dir) {
    node.position.x += dir.x;
    node.position.y += dir.y;
    node.position.z += dir.z;
  }


  inline void node3DIncreaseRotation(Node3D &node, float rx, float ry, float rz) {
    node.rotation.x += rx;
    node.rotation.y += ry;
    node.rotation.z += rz;
  }
  
  
  inline void node3DIncreaseRotation(Node3D &node, glm::vec3 rot) {
    node.rotation.x += rot.x;
    node.rotation.y += rot.y;
    node.rotation.z += rot.z;
  }
}