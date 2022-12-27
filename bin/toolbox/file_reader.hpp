#pragma once

#include "types.hpp"

namespace mke {
  inline String getFileBinData(const String &filename) {
    std::string data;
    std::ifstream file(filename, std::ios::binary);

    if (file) {
        // Get the file size
        file.seekg(0, std::ios::end);
        size_t fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        // Allocate a buffer to store the data
        char* buffer = new char[fileSize];

        // Read the data into the buffer
        file.read(buffer, fileSize);

        // Copy the data from the buffer into the string
        data.assign(buffer, fileSize);

        // Clean up the buffer
        delete[] buffer;
    }
    return data;
  }


  inline String getFileData(const String &filename) {
    String data, line;
    std::ifstream file(filename);
    if (file.is_open()) {
      while (std::getline(file, line))
        data += line + '\n';
    }
    file.close();
    return data;
  }

  
}