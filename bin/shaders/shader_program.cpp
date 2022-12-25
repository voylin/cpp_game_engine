#include "shader_program.hpp"

namespace mke {
  ShaderProgram createShaderProgram(String vertexFile, String fragmentFile){
    GLuint vertID = loadShader(vertexFile, GL_VERTEX_SHADER);
    GLuint fragID = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
    GLuint progID = glCreateProgram();
    ShaderProgram program{progID, vertID, fragID};

    glAttachShader(program.programID, program.vertexShaderID);
    glAttachShader(program.programID, program.fragmentShaderID);

    bindAttributes(program);
    glLinkProgram(program.programID);
    glValidateProgram(program.programID);
    int success;
    char infoLog[1024];
    glGetProgramiv(program.programID, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(program.programID, 1024, NULL, infoLog);
      throw printFatal("Shader program linking has failed!\n\tDetails: '" + static_cast<String>(infoLog) + "'!");
    }

    glDeleteShader(program.vertexShaderID);
    glDeleteShader(program.fragmentShaderID);

    return program;
  }


  void createStaticShader(){
    ShaderProgram shaderProgram = createShaderProgram(SIMPLE_VERT_FILE, SIMPLE_FRAG_FILE);
    GLuint location_transformationMatrix = getUniformLocation(shaderProgram, "transformationMatrix");
    GLuint location_projectionMatrix = getUniformLocation(shaderProgram, "projectionMatrix");
    GLuint location_viewMatrix = getUniformLocation(shaderProgram, "viewMatrix");

    staticShader = StaticShader{shaderProgram, location_transformationMatrix, location_projectionMatrix, location_viewMatrix};
  }


  void startShaderProgram(ShaderProgram program) {
    glUseProgram(program.programID);
  }


  void stopShaderProgram() {
    glUseProgram(0);
  }


  void bindAttribute(ShaderProgram program, int attribute, String variableName) {
    glBindAttribLocation(program.programID, attribute, variableName.c_str());
  }


  GLuint getUniformLocation(ShaderProgram program, String uniformName) { 
    return glGetUniformLocation(program.programID, uniformName.c_str());
  }


  void bindAttributes(ShaderProgram program) {
    bindAttribute(program, 0, "position");
    bindAttribute(program, 1, "textureCoords");
  }


  void cleanUpShaderProgram(ShaderProgram program) {
    stopShaderProgram();
    glDetachShader(program.programID, program.vertexShaderID);
    glDetachShader(program.programID, program.fragmentShaderID);
    glDeleteProgram(program.programID);
  }


  void loadBool(GLuint location, bool value) {
    glUniform1f(location, value ? 1 : 0);
  }


  void loadFloat(GLuint location, float value) {
    glUniform1f(location, value);
  }


  void loadVector(GLuint location, glm::vec3 vector) {
    glUniform3f(location, vector.x, vector.y, vector.z);
  }


  void loadVector(GLuint location, float vectorX, float vectorY, float vectorZ) {
    glUniform3f(location, vectorX, vectorY, vectorZ);
  }


  void loadMatrix(GLuint location, glm::mat4 matrix) {
    glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
  }


  void loadTransformationMatrix(StaticShader shader, glm::mat4 matrix) {
    loadMatrix(shader.location_transformationMatrix, matrix);
  }


  void loadProjectionMatrix(StaticShader shader, glm::mat4 matrix) {
    loadMatrix(shader.location_projectionMatrix, matrix);
  }


  void loadViewMatrix(StaticShader shader, Camera camera) {
    glm::mat4 viewMatrix = createViewMatrix(camera);
    loadMatrix(shader.location_viewMatrix, viewMatrix);
  }


  GLuint loadShader(String filePath, int type) {
    // Read file
    String shaderCode;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
      shaderFile.open("shaders/" + filePath);
      std::stringstream shaderStream;
      shaderStream << shaderFile.rdbuf();
      shaderFile.close();
      shaderCode = shaderStream.str();
    } catch (std::ifstream::failure e)
    { throw printFatal("Shader file not successfully read!\n\tDetails: '" + static_cast<String>(e.what()) + "'!"); }

    // Make the shader
    GLuint shaderID = glCreateShader(type);
    const char *shaderSource = shaderCode.c_str();
    glShaderSource(shaderID, 1, &shaderSource, NULL);
    glCompileShader(shaderID);
    int success;
    char infoLog[1024];
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
      throw printFatal("Shader compilation failed!\n\tDetails: '" + static_cast<String>(infoLog) + "'!");
    }
    return shaderID;
  }
}