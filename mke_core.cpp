#include "mke_core.hpp"


namespace mke {
  void startEngine(const String *game_name, const Version *game_version) {
    printInfo("Starting " + ENGINE_NAME);
    printInfo("Engine version: " + ENGINE_VERSION.toString())
    printInfo("GLFW: " + static_cast<String>(glfwGetVersionString()));
    printInfo("OpenGL: " + OPEN_GL_VERSION.toSmallString());
    printInfo("Game name: " + *game_name);
    printInfo("Game version: " + game_version->toString());

    GAME_NAME = game_name;
    GAME_VERSION = game_version;

    initWindow();
    createStaticShader(); // Main shader creation
    createProjectionMatrix();

    // Setting callbacks:
    glfwSetKeyCallback(window_id, inputKeyCallBack);

    run();
  }


  static void run() {
    printEngine("Starting loop.");

    initTime();
    // Temp Code:
    v_Vertex vertices = {
      {-0.5f,  0.5f, 0.f},  // V0
      {-0.5f, -0.5f, 0.f},  // V1
      { 0.5f, -0.5f, 0.f},  // V2
      { 0.5f,  0.5f, 0.f}   // V3
    };
    v_uint indices = {
      0,1,3,  // Top left
      3,1,2   // Bottom Right
    };
    v_TexCoord textureCoords = {
      {0,0},  // V0
      {0,1},  // V1
      {1,1},  // V2
      {1,0}   // V3
    };

    //Model model = loadToVAO(vertices, textureCoords, indices, Texture{loadTexture("wall.jpg")});
    Model model = loadGLTF("models/test.gltf");
    Node3D node{model, glm::vec3(0, 0, -20), glm::vec3(0), 1.0f};
    // End Temp

    setDeltaStartTimes();
    while (!glfwWindowShouldClose(window_id)) {
      // Input processing:
      processInput();

      // Render stuff:
      // Temp stuff
      prepareRenderer();
      startShaderProgram(staticShader.shaderProgram);
      node3DIncreaseRotation(node, {0.01,0.01,0});
      loadViewMatrix(staticShader, mainCamera);
      render(node);
      stopShaderProgram();
      // End Temp

      // Poll and Swapping:
      glfwSwapBuffers(window_id);
      glfwPollEvents();


      setDeltaTimes();
    }

    glfwWaitEvents();
    shutdownEngine();
  }


  static void shutdownEngine() {
    printEngine("Shutting down engine.");

    cleanUpShaderProgram(staticShader.shaderProgram);
    cleanUpModelManager();
    closeWindow();

    printEngine("Shutdown complete!");
  }
}