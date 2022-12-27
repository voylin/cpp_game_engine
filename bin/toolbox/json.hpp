#pragma once

#include "types.hpp"
#include "logger.hpp"

// TODO: Check if I can make some of these functions static instead.


namespace mke {
  // Parse a JSON string and return the resulting value
  extern JsonValue parseJson(const std::string &json);
  extern JsonValue parseJsonFile(const std::string &filename);
  
  extern JsonValue _checkJsonValue(const JsonValue &value, const String &name, const JsonType type);

  // Get's and checks if the value is the specified type, else throws an error.
  extern JsonValue getJsonValue(const JsonValue &value, const String &name);

  extern String getJsonString(const JsonValue &value, const String &name);
  extern double getJsonDouble(const JsonValue &value, const String &name);
  extern bool getJsonBool(const JsonValue &value, const String &name);
  extern v_JsonValue getJsonArray(const JsonValue &value, const String &name);
  extern dic_JsonValue getJsonObject(const JsonValue &value, const String &name);

  // Parser functions for different value types
  extern JsonValue _parseJsonValue(const std::string &json, size_t &pos);
  extern JsonValue _parseJsonString(const String &json, size_t &pos);
  extern JsonValue _parseJsonNum(const String &json, size_t &pos);
  extern JsonValue _parseJsonBool(const String &json, size_t &pos);
  extern JsonValue _parseJsonNull(const String &json, size_t &pos);
  extern JsonValue _parseJsonArray(const String &json, size_t &pos);
  extern JsonValue _parseJsonObject(const String &json, size_t &pos);

  extern void _skipWhitespace(const String &json, size_t &pos);
}