#include "../include/FileLoader.hpp"

#include <fstream>

#include "../include/exceptions.h"
#include "../include/utils.hpp"

FileLoader::FileLoader(std::string path) {
    try {
        bytes = NULL;
        std::ifstream fin;
        fin.open(path);
        fileSize = get_file_size(path);
        bytes = new char[fileSize];
        fin.read(bytes, fileSize);
        contentType = get_file_type(path);
    } catch (const std::exception& e) {
        throw FileRelatedException("FileLoader Init Error");
    }
}

FileLoader::~FileLoader() {
    if (bytes) delete[] bytes;
}

const char* FileLoader::getBytes() { return bytes; }
std::size_t FileLoader::getFileSize() { return fileSize; }
std::string FileLoader::getContentType() { return contentType; }
