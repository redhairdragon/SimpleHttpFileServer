#ifndef FileLoader_H
#define FileLoader_H
#include <memory>
#include <string>
class FileLoader {
   public:
    FileLoader(std::string path);
    ~FileLoader();

    const char* getBytes();
    std::size_t getFileSize();
    std::string getContentType();

   private:
    char* bytes;
    std::string contentType;
    std::size_t fileSize;
};
#endif
