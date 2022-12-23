#include "mke_core.hpp"


namespace mke {
  void startEngine(const String *game_name, const Version *game_version) {
    print_info("Starting " + ENGINE_NAME);
    print_info("Engine version: " + ENGINE_VERSION.toString())
    print_info("GLFW: " + static_cast<String>(glfwGetVersionString()));
    print_info("OpenGL: " + OPEN_GL_VERSION.toSmallString());
    print_info("Game name: " + *game_name);
    print_info("Game version: " + game_version->toString());

    GAME_NAME = game_name;
    GAME_VERSION = game_version;

    initWindow();
    initTime();
    createStaticShader(); // Main shader creation
    createProjectionMatrix(staticShader);

    // Setting callbacks:
    glfwSetKeyCallback(window_id, inputKeyCallBack);

    run();
  }


  static void run() {
    print_engine("Starting loop.");
    // Temp Code:
    std::vector<float> vertices = {
      -0.5f,  0.5f, 0.f,  // V0
      -0.5f, -0.5f, 0.f,  // V1
       0.5f, -0.5f, 0.f,  // V2
       0.5f,  0.5f, 0.f   // V3
    };
    std::vector<unsigned int> indices = {
      0,1,3,  // Top left
      3,1,2   // Bottom Right
    };
    std::vector<float> textureCoords = {
      0,0,  // V0
      0,1,  // V1
      1,1,  // V2
      1,0   // V3
    };

    RawModel model = loadToVAO(vertices, textureCoords, indices);
    Texture texture{loadTexture("wall.jpg")};

    TexturedModel texturedModel{model, texture};

    Node3D node{texturedModel, glm::vec3(0, 0, -5), glm::vec3(0), 1.0f};
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
      render(node, staticShader);
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
    print_engine("Shutting down engine.");

    cleanUpShaderProgram(staticShader.shaderProgram);
    cleanUpModelManager();
    closeWindow();

    print_engine("Shutdown complete!");
  }
}