#pragma once

#include "types.hpp"
#include "logger.hpp"

// TODO: Check if I can make some of these functions static instead.


namespace mke {
  extern JsonValue parseJson(const std::string& json);

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