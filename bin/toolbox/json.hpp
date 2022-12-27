#pragma once

#include "types.hpp"
#include "logger.hpp"

// TODO: Check if I can make some of these functions static instead.


namespace mke {
  // Parse a JSON string and return the resulting value
  extern JsonValue parseJson(const std::string& json);
  
  // Get's and checks if the value is the specified type, else throws an error.
  extern JsonValue getJsonValue(const JsonValue &value, const JsonType type);

  // Parser functions for different value types
  extern JsonValue _parseJsonValue(const std::string& json, size_t& pos);
  extern JsonValue _parseJsonString(const String &json, size_t &pos);
  extern JsonValue _parseJsonNum(const String &json, size_t &pos);
  extern JsonValue _parseJsonBool(const String &json, size_t &pos);
  extern JsonValue _parseJsonNull(const String &json, size_t &pos);
  extern JsonValue _parseJsonArray(const String &json, size_t &pos);
  extern JsonValue _parseJsonObject(const String &json, size_t &pos);

  extern void _skipWhitespace(const String &json, size_t &pos);
}