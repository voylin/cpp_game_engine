#include "renderer.hpp"


namespace mke {
  void prepareRenderer() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.7f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }


  void render(Node3D node) {
    Model model = node.model;
    glBindVertexArray(model.vaoID);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glm::mat4 transformationMatrix = createTransformationMatrix(node.position, node.rotation, node.scale);
    loadTransformationMatrix(staticShader, transformationMatrix);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, model.texture.textureID);
    glDrawElements(GL_TRIANGLES, model.vertexCount, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindVertexArray(0);
  }
}