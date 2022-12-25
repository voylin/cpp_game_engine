#pragma once
#include "types.hpp"

/*  Logger
  The logger is meant for printing messages and saving log files.

  TODO:
  - Create a way to store the log to a file without all the color code stuff;
  - Do something with the extra info '...'.
*/

enum class LogLevel {Info, Engine, Game, Error, Fatal}; 


// Printing log message to console
inline void printLog(LogLevel level, const String message) {
  String level_string;

  switch (level) {
    case LogLevel::Info:
      level_string = "\033[32;1m[INFO]: \033[0;32m";
      break;
    case LogLevel::Engine:
      level_string = "\033[90;1m[Engine]: \033[0;90m";
      break;
    case LogLevel::Game:
      level_string = "\033[1m[GAME]: \033[0m";
      break;
    case LogLevel::Error:
      level_string = "\033[31;1m[ERROR]: \033[0;31m";
      break;
    case LogLevel::Fatal:
      level_string = "\033[31;1m[FATAL]: \033[0;31m";
      break;
  }
  
  std::cerr << level_string << message << "\033[0m" << std::endl;
}


inline std::runtime_error printError(const String message) {
  printLog(LogLevel::Error, message);
  return std::runtime_error{"[ERROR]: " + message};;
}


inline std::runtime_error printFatal(const String message) {
  printLog(LogLevel::Fatal, message);
  return std::runtime_error{"[FATAL]: " + message};
}


// Callback function for GLFW error messages
inline void glfw_error_callback(int err_code, const char *description) {
  printError("GLFW error code: '" + std::to_string(err_code) + "'.\n\tDescription: " + static_cast<String>(description));
}


// Macros to make calling the printLog function easier
#define printInfo(message) printLog(LogLevel::Info, message);
#define printEngine(message) printLog(LogLevel::Engine, message); // For in-engine related code
#define printGame(message) printLog(LogLevel::Game, message);     // For in-game related code
