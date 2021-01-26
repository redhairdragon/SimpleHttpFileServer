#include "../include/Response.hpp"

#include <unistd.h>

#include "../include/exceptions.h"

const std::string BAD_RESPONSE =
    "HTTP/1.0 404 Not Found\r\nContent-Type:text/html\r\nContent-Length:  "
    "12\r\nConnection: close\r\n\r\n<h2>404</h2>";

Response::Response(int clientSocketFd)
    : clientSocketFd(clientSocketFd), payloadPtr(NULL), payloadLen(0) {}

void Response::badResponse() {
    header = BAD_RESPONSE;
    payloadPtr = NULL;
    payloadLen = 0;
}

void Response::successResponse(const char* payload, std::size_t len,
                               std::string contentType) {
    payloadPtr = payload;
    payloadLen = len;

    std::string status_line = string("HTTP/1.1 200 OK\r\n");
    std::string content_length = std::string("Content-Length:") +
                                 std::to_string(len) + std::string("\r\n");
    std::string content_type =
        std::string("Content-Type:") + contentType + std::string("\r\n");
    std::string connection = std::string("Connection: Closed\r\n\r\n");
    header += status_line;
    header += content_length;
    header += content_type;
    header += connection;
}

void Response::writeToSocket(const char* data, std::size_t len) {
    int sent_cnt = 0;
    while (sent_cnt != len) {  // This loop ensures all data are sent out
        int n = write(clientSocketFd, &data[sent_cnt], len - sent_cnt);
        if (n < 0) throw ResponseException("ERROR writing to socket");
        sent_cnt += n;
    }
}

void Response::send() {
    writeToSocket(header.c_str(), header.size());
    if (payloadPtr) writeToSocket(payloadPtr, payloadLen);
}
std::size_t Response::getPayloadLength() { return payloadLen; }
const char* Response::getPayloadPointer() { return payloadPtr; }
std::string Response::getHeader() { return header; }
