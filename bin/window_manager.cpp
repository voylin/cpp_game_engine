#include "window_manager.hpp"


namespace mke {
  uint32_t window_width = 1920;
  uint32_t window_height = 1080;


    void initWindow() {
    // Connects to the error callback inside of 'logger'.
    glfwSetErrorCallback(glfw_error_callback);

    if (!glfwInit())
      throw printFatal("Unable to initialize GLFW!");

    // Configuring GLFW:
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPEN_GL_VERSION.major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPEN_GL_VERSION.minor);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creating the window:
    String window_title = *GAME_NAME + " - " + GAME_VERSION->toString();
    window_id = glfwCreateWindow(
      window_width,
      window_height,
      window_title.c_str(),
      nullptr,
      nullptr
    );

    if (window_id == nullptr)
      throw printFatal("Failed to create window!");

    glfwMakeContextCurrent(window_id);

    // Loading OpenGL function pointers:
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      glfwDestroyWindow(window_id);
      glfwTerminate();
      throw printFatal("GLAD could not initialize!");
    }

    glViewport(0, 0, window_width, window_height);

    glfwSwapInterval(1); // Enable buffer swapping (V-Sync)
    glfwShowWindow(window_id); // Now that window is ready, make it visible

    glfwSetFramebufferSizeCallback(window_id, frameBufferSizeCallback);
  }


  void closeWindow() {
    glfwDestroyWindow(window_id);
    glfwTerminate();
  }


  void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    window_width = width;
    window_height = height;
    glViewport(0, 0, width, height);
    createProjectionMatrix();
  }
}