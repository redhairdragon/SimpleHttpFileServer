#ifndef REQUEST_H
#define REQUEST_H
#include <string>

class Request {
   public:
    Request(const std::string& raw);
    std::string getFilePath() { return filePath; }
    bool isSupported() { return supported; };

   private:
    bool supported;

    bool validate(const std::string& raw);
    std::string parseFilePath(const std::string& raw);
    std::string filePath;
};
#endif
