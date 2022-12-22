#pragma once

#include "types.hpp"
#include "../camera.hpp"


namespace mkeMath {
  inline glm::mat4 createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale) {
    glm::mat4 transform{1.0f};

    transform = glm::translate(transform, translation);

    transform = glm::rotate(transform, (float)rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, (float)rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, (float)rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    transform = glm::scale(transform, glm::vec3(scale));

    return transform;
  }


  inline glm::mat4 createViewMatrix(mkeCamera::Camera camera) {
    glm::mat4 viewMatrix{1.0f};

    viewMatrix = glm::rotate(viewMatrix, (float)glm::radians(camera.pitch), glm::vec3{1,0,0});
    viewMatrix = glm::rotate(viewMatrix, (float)glm::radians(camera.yaw), glm::vec3{0,1,0});

    glm::vec3 cameraPos = camera.position;
    glm::vec3 negativeCameraPos = glm::vec3{-cameraPos.x, -cameraPos.y, -cameraPos.z};
    viewMatrix = glm::translate(viewMatrix, negativeCameraPos);

    return viewMatrix;
  }
}