#include "mke_core.hpp"


void mkeCore::startEngine(const String *game_name, const Version *game_version) {
  print_info("Starting " + ENGINE_NAME);
  print_info("Engine version: " + ENGINE_VERSION.toString())
  print_info("GLFW: " + static_cast<String>(glfwGetVersionString()));
  print_info("OpenGL: " + OPEN_GL_VERSION.toSmallString());
  print_info("Game name: " + *game_name);
  print_info("Game version: " + game_version->toString());

  GAME_NAME = game_name;
  GAME_VERSION = game_version;

  mkeWindow::init();
  mkeTime::init();

  // Setting callbacks:
  glfwSetFramebufferSizeCallback(mkeWindow::window_id, mkeWindow::frameBufferSizeCallback);
  glfwSetKeyCallback(mkeWindow::window_id, mkeInput::inputKeyCallBack);

  run();
}


void mkeCore::run() {
  print_engine("Starting loop.");

  // Main shader creation
  mkeShaderProgram::createStaticShader();

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

  RawModel model = mkeModelManager::loadToVAO(vertices, textureCoords, indices);
  Texture texture{mkeModelManager::loadTexture("wall.jpg")};
  
  TexturedModel texturedModel{model, texture};

  mkeNode3D::Node3D node{texturedModel, glm::vec3(0, 0, -5), glm::vec3(0), 1.0f};

  mkeRenderer::createProjectionMatrix(mkeShaderProgram::staticShader);
  // End Temp

  mkeTime::setDeltaStartTimes();
  while (!glfwWindowShouldClose(mkeWindow::window_id)) {
    // Input processing:
    mkeInput::processInput();

    // Render stuff:
    // Temp stuff
    mkeRenderer::prepare();
    mkeShaderProgram::start(mkeShaderProgram::staticShader.shaderProgram);
    mkeNode3D::increaseRotation(node, {0.01,0.01,0});
    mkeShaderProgram::loadViewMatrix(mkeShaderProgram::staticShader, mkeCamera::mainCamera);
    mkeRenderer::render(node, mkeShaderProgram::staticShader);
    mkeShaderProgram::stop();
    // End Temp

    // Poll and Swapping:
    glfwSwapBuffers(mkeWindow::window_id);
    glfwPollEvents();

    
    mkeTime::setDeltaTimes();
    print_engine(std::to_string(mkeTime::getFPS()));
  }
  
  glfwWaitEvents();
  shutdownEngine();
}


void mkeCore::shutdownEngine() {
  print_engine("Shutting down engine.");
  
  mkeShaderProgram::cleanUp(mkeShaderProgram::staticShader.shaderProgram);
  mkeModelManager::cleanUp();
  mkeWindow::closeWindow();

  print_engine("Shutdown complete!");
}
