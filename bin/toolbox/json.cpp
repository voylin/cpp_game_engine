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
          default: throw std::runtime_error("Unexpected escape character sequence at position " + std::to_string(pos));
        }
      } else value += json[pos]; // Otherwise, add the character to the string value

      pos++;
    }

    JsonValue result;
    result.type = JsonType::String;
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
    result.type = JsonType::Number;
    result.numValue = std::stod(value);
    return result;
  }


  JsonValue _parseJsonBool(const String &json, size_t &pos) {
    JsonValue result;
    result.type = JsonType::Bool;

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
    result.type = JsonType::Null;
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
        throw std::runtime_error("Unexpected array character at position " + std::to_string(pos));
    }

    JsonValue result;
    result.type = JsonType::Array;
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
        throw std::runtime_error("Unexpected object character at position " + std::to_string(pos));
    }

    JsonValue result;
    result.type = JsonType::Object;
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

  
  JsonValue parseJson(const std::string &json) {
    size_t pos = 0;
    return _parseJsonValue(json, pos);
  }


  JsonValue parseJsonFile(const std::string &filename) {
    return parseJson(getFileData(filename));
  }


  JsonValue _checkJsonValue(const JsonValue &value, const String &name, const JsonType type) {
    JsonValue jsonValue = value.objectValue.at(name);
    if (jsonValue.type != type) {
      switch (type) { 
        case JsonType::Number: throw printError("Expected value type to be a Number!");
        case JsonType::String: throw printError("Expected value type to be a String!");
        case JsonType::Bool:   throw printError("Expected value type to be a Bool!");
        case JsonType::Null:   throw printError("Expected value type to be a Null!");
        case JsonType::Array:  throw printError("Expected value type to be an Array!");
        case JsonType::Object: throw printError("Expected value type to be an Object!");
        default: throw printError("Unknown type!");
      }
    }
    return jsonValue;
  }


  JsonValue getJsonValue(const JsonValue &value, const String &name) {
    return value.objectValue.at(name);
  }


  String getJsonString(const JsonValue &value, const String &name) {
    return _checkJsonValue(value, name, JsonType::String).stringValue;
  }


  double getJsonDouble(const JsonValue &value, const String &name) {
    return _checkJsonValue(value, name, JsonType::Number).numValue;
  }


  bool getJsonBool(const JsonValue &value, const String &name) {
    return _checkJsonValue(value, name, JsonType::Bool).boolValue;
  }


  v_JsonValue getJsonArray(const JsonValue &value, const String &name) {
    return _checkJsonValue(value, name, JsonType::Array).arrayValue;
  }


  dic_JsonValue getJsonObject(const JsonValue &value, const String &name) {
    return _checkJsonValue(value, name, JsonType::Object).objectValue;
  }




  void _skipWhitespace(const String &json, size_t &pos) {
    while (pos < json.size() && isspace(json[pos]))
      pos++;
  }

}