#include "renderer.hpp"


namespace mkeRenderer {
  void prepare() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.7f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }
 

  void render(RawModel model) {
    glBindVertexArray(model.vaoID);
    glEnableVertexAttribArray(0);
    glDrawElements(GL_TRIANGLES, model.vertexCount, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
  }


  void render(TexturedModel texturedModel) {
    RawModel model = texturedModel.rawModel;
    glBindVertexArray(model.vaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturedModel.texture.textureID);
    glDrawElements(GL_TRIANGLES, model.vertexCount, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
  }


  void render(mkeNode3D::Node3D node, mkeShaderProgram::StaticShader shader) {
    TexturedModel model = node.model;
    RawModel rawModel = model.rawModel;
    glBindVertexArray(rawModel.vaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glm::mat4 transformationMatrix = mkeMath::createTransformationMatrix(node.position, node.rotation, node.scale);
    mkeShaderProgram::loadTransformationMatrix(shader, transformationMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.texture.textureID);
    glDrawElements(GL_TRIANGLES, rawModel.vertexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
  }
 
  void createProjectionMatrix(mkeShaderProgram::StaticShader shader) {
    float aspectRatio = static_cast<float>(mkeWindow::window_width) / static_cast<float>(mkeWindow::window_height); 
    float y_scale = static_cast<float>(((1.0f /glm::tan(glm::radians(FOV/2.0f)))) * aspectRatio);
    float x_Scale = y_scale / aspectRatio;
    float frustum_length = FAR_PLANE - NEAR_PLANE;
  
    projectionMatrix = glm::mat4{};
    projectionMatrix[0][0] = x_Scale;
    projectionMatrix[1][1] = y_scale;
    projectionMatrix[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
    projectionMatrix[2][3] = -1;
    projectionMatrix[3][2] = -((2 * NEAR_PLANE * FAR_PLANE) / frustum_length);
    projectionMatrix[3][3] = 0;
  
    mkeShaderProgram::start(shader.shaderProgram);
    mkeShaderProgram::loadProjectionMatrix(shader, projectionMatrix);
    mkeShaderProgram::stop();
  }
}