#include "math.hpp"


namespace mke {
  glm::mat4 createTransformationMatrix(glm::vec3 translation, glm::vec3 rotation, float scale) {
    glm::mat4 transform{1.0f};

    transform = glm::translate(transform, translation);

    transform = glm::rotate(transform, (float)rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, (float)rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, (float)rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

    transform = glm::scale(transform, glm::vec3(scale));

    return transform;
  }


  glm::mat4 createViewMatrix(Camera camera) {
    glm::mat4 viewMatrix{1.0f};

    viewMatrix = glm::rotate(viewMatrix, (float)glm::radians(camera.pitch), glm::vec3{1,0,0});
    viewMatrix = glm::rotate(viewMatrix, (float)glm::radians(camera.yaw), glm::vec3{0,1,0});

    glm::vec3 cameraPos = camera.position;
    glm::vec3 negativeCameraPos = glm::vec3{-cameraPos.x, -cameraPos.y, -cameraPos.z};
    viewMatrix = glm::translate(viewMatrix, negativeCameraPos);

    return viewMatrix;
  }

  
  void createProjectionMatrix(StaticShader shader) {
    const float RENDER_FOV = 70.0f;
    const float RENDER_NEAR_PLANE = 0.1f;
    const float RENDER_FAR_PLANE = 1000.0f;

    float aspectRatio = static_cast<float>(window_width) / static_cast<float>(window_height); 
    float y_scale = static_cast<float>(((1.0f /glm::tan(glm::radians(RENDER_FOV/2.0f)))) * aspectRatio);
    float x_Scale = y_scale / aspectRatio;
    float frustum_length = RENDER_FAR_PLANE - RENDER_NEAR_PLANE;
  
    projectionMatrix = glm::mat4{};
    projectionMatrix[0][0] = x_Scale;
    projectionMatrix[1][1] = y_scale;
    projectionMatrix[2][2] = -((RENDER_FAR_PLANE + RENDER_NEAR_PLANE) / frustum_length);
    projectionMatrix[2][3] = -1;
    projectionMatrix[3][2] = -((2 * RENDER_NEAR_PLANE * RENDER_FAR_PLANE) / frustum_length);
    projectionMatrix[3][3] = 0;
  
    startShaderProgram(shader.shaderProgram);
    loadProjectionMatrix(shader, projectionMatrix);
    stopShaderProgram();
  }
}