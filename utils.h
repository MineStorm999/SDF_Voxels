#pragma once
#include <vector>
#include <string>
#include <fstream>

inline std::vector<char> ReadFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error(std::string("Failed to open file ") + filename + "!");
    }

    size_t file_size = (size_t)file.tellg();
    std::vector<char> buffer(file_size);

    file.seekg(0);
    file.read(buffer.data(), static_cast<std::streamsize>(file_size));
    file.close();

    return buffer;
}

enum ErrorCode : int{
    Error = -666,
};