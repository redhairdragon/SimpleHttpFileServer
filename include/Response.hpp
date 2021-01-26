#ifndef RESPONSE_H
#define RESPONSE_H
#include <string>

class Response {
   public:
    Response(int clientSocketFd);
    void badResponse();
    void successResponse(const char* payload, std::size_t len,
                         std::string contentType);
    void send();
    std::size_t getPayloadLength();
    const char* getPayloadPointer();
    std::string getHeader();

    ~Response(){};

   private:
    int clientSocketFd;

    std::string header;
    const char* payloadPtr;
    std::size_t payloadLen;

    void writeToSocket(const char* data, std::size_t len);
};
#endif
