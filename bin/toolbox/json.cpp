#include "json.hpp"

namespace mke {
  JsonValue _parseJsonString(const String &json, size_t &pos) {
    String value;

    pos++;   // Skip the opening quote

    while (pos < json.size()) {
      if (json[pos] == '"') {  // Check for end
        pos++;
        break;
      } else if (json[pos] == '\\') {  // Check for escape sequence
        pos++;

        if (pos == json.size())
          throw std::runtime_error("Unexpected end of input at position " + std::to_string(pos));

        // Handle specific escape sequences
        switch (json[pos]) {
          case '"':
            value += '"';
            break;
          case '\\':
            value += '\\';
            break;
          case '/':
            value += '/';
            break;
          case 'b':
            value += '\b';
            break;
          case 'f':
            value += '\f';
            break;
          case 'n':
            value += '\n';
            break;
          case 'r':
            value += '\r';
            break;
          case 't':
            value += '\t';
            break;
          default: throw std::runtime_error("Unexpected character at position " + std::to_string(pos));
        }
      } else value += json[pos]; // Otherwise, add the character to the string value

      pos++;
    }

    JsonValue result;
    result.type = JsonValue::JsonType::String;
    result.stringValue = value;
    return result;
  }


  JsonValue _parseJsonNum(const String &json, size_t &pos) {
    String value;

    // Check for negative
    if (json[pos] == '-') {
      value += json[pos];
      pos++;
    }

    // Parse the integer part of the number
    while (pos < json.size() && isdigit(json[pos])) {
      value += json[pos];
      pos++;
    }

    // Check for a decimal point
    if (pos < json.size() && json[pos] == '.') {
      value += json[pos];
      pos++;

      // Parse the fractional part of the number
      while (pos < json.size() && isdigit(json[pos])) {
        value += json[pos];
        pos++;
      }
    }

    // Check for an exponent
    if (pos < json.size() && (json[pos] == 'e' || json[pos] == 'E')) {
      value += json[pos];
      pos++;

      // Check for a positive or negative exponent
      if (pos < json.size() && (json[pos] == '+' || json[pos] == '-')) {
        value += json[pos];
        pos++;
      }

      // Parse the exponent
      while (pos < json.size() && isdigit(json[pos])) {
        value += json[pos];
        pos++;
      }
    }

    JsonValue result;
    result.type = JsonValue::JsonType::Number;
    result.numValue = std::stod(value);
    return result;
  }


  JsonValue _parseJsonBool(const String &json, size_t &pos) {
    JsonValue result;
    result.type = JsonValue::JsonType::Bool;

    if (json[pos] == 't') {
      result.boolValue = true;
      pos += 4;
    } else {
      result.boolValue = false;
      pos += 5;
    }
    return result;
  }


  JsonValue _parseJsonNull(const String &json, size_t &pos) {
    JsonValue result;
    result.type = JsonValue::JsonType::Null;
    pos += 4;
    return result;
  }


  JsonValue _parseJsonArray(const String &json, size_t &pos) {
    // Skip the opening bracket
    pos++;

    std::vector<JsonValue> values;
    while (pos < json.size())
    {
      _skipWhitespace(json, pos);

      // Check for the closing bracket
      if (json[pos] == ']')
      {
        // End of the array, skip the closing bracket and return the values
        pos++;
        break;
      }

      // Parse the next value in the array
      values.push_back(_parseJsonValue(json, pos));

      _skipWhitespace(json, pos);

      // Check for the comma separator
      if (json[pos] == ',')
        pos++;
      else if (json[pos] != ']')
        throw std::runtime_error("Unexpected character at position " + std::to_string(pos));
    }

    JsonValue result;
    result.type = JsonValue::JsonType::Array;
    result.arrayValue = values;
    return result;
  }


  JsonValue _parseJsonObject(const String &json, size_t &pos) {
    // Skip the opening brace
    pos++;

    std::unordered_map<String, JsonValue> values;
    while (pos < json.size())
    {
      _skipWhitespace(json, pos);

      // Check for the closing brace
      if (json[pos] == '}') {
        pos++;
        break;
      }

      // Parse the next key-value pair in the object
      String key = _parseJsonString(json, pos).stringValue;

      // Skip any leading whitespace
      _skipWhitespace(json, pos);

      // Expect a colon separator
      if (json[pos] != ':') {
        throw std::runtime_error("Expected ':' at position " + std::to_string(pos));
      }
      pos++;

      _skipWhitespace(json, pos);

      // Parse the next value in the object
      JsonValue value = _parseJsonValue(json, pos);

      // Add the key-value pair to the map
      values[key] = value;

      _skipWhitespace(json, pos);

      // Check for the comma separator
      if (json[pos] == ',')
        pos++;
      else if (json[pos] != '}')
        throw std::runtime_error("Unexpected character at position " + std::to_string(pos));
    }

    JsonValue result;
    result.type = JsonValue::JsonType::Object;
    result.objectValue = values;
    return result;
  }


  JsonValue _parseJsonValue(const std::string& json, size_t& pos)
  {
    _skipWhitespace(json, pos);

    if (json[pos] == '"')                             // Check for the start of a string
      return _parseJsonString(json, pos); 
    else if (isdigit(json[pos]) || json[pos] == '-')  // Check for the start of a number
      return _parseJsonNum(json, pos);
    else if (json[pos] == 't' || json[pos] == 'f')    // Check for the start of a boolean value
      return _parseJsonBool(json, pos);
    else if (json[pos] == 'n')                        // Check for the start of a null value
      return _parseJsonNull(json, pos);
    else if (json[pos] == '[')                        // Check for the start of an array
      return _parseJsonArray(json, pos);
    else if (json[pos] == '{')                        // Check for the start of an object
      return _parseJsonObject(json, pos);
    else throw std::runtime_error("Unexpected character at position " + std::to_string(pos));
  }

  // Parse a JSON string and return the resulting value
  JsonValue parseJson(const std::string& json) {
    size_t pos = 0;
    return _parseJsonValue(json, pos);
  }


  void _skipWhitespace(const String &json, size_t &pos) {
    while (pos < json.size() && isspace(json[pos]))
      pos++;
  }

}