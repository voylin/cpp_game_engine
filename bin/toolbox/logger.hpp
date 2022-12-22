#pragma once
#include "types.hpp"

/*  Logger
  The logger is meant for printing messages and saving log files.

  TODO:
  - Create a way to store the log to a file without all the color code stuff;
  - Do something with the extra info '...'.
*/

enum log_level {LOG_LEVEL_INFO, LOG_LEVEL_ENGINE, LOG_LEVEL_LINE}; 


inline void printLog(log_level level, const String message, ...) {
  const char *level_string[] = {
    "\033[32;1m[INFO]: \033[0;32m",
    "\033[90;1m[Engine]: \033[0;90m",
    "\033[1m[GAME]: \033[0m"};
  std::cerr << level_string[level] << message << "\033[0m" << std::endl;
}


inline std::runtime_error print_error(const String message, ...) {
  std::cerr << "\033[31;1m[ERROR]: \033[0;31m" << message << "\033[0m" << std::endl;
  return std::runtime_error{"[ERROR]: " + message};;
}


inline std::runtime_error print_fatal(const String message, ...) {
  std::cerr << "\033[31;1m[FATAL]: \033[0;31m" << message << "\033[0m" << std::endl;
  return std::runtime_error{"[FATAL]: " + message};
}


inline void glfw_error_callback(int error_code, const char *description) {
  print_error("GLFW error code: '" + std::to_string(error_code) + "'.\n\tDescription: " + static_cast<String>(description));
}


// These defines make it easier in code for calling the printLog function.
#define print_info(message, ...) printLog(LOG_LEVEL_INFO, message, ##__VA_ARGS__);
#define print_engine(message, ...) printLog(LOG_LEVEL_ENGINE, message, ##__VA_ARGS__); // For in-engine related code
#define print_line(message, ...) printLog(LOG_LEVEL_LINE, message, ##__VA_ARGS__); // For in-game related code
