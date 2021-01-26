#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>
using std::exception;
using std::string;
class SocketsInitFailedException : public exception {
   public:
    SocketsInitFailedException(const char* reason_) : reason(reason_) {}
    const char* what() const throw() { return reason; }
    const char* reason;
};
class ConnectionFailedException : public exception {
   public:
    ConnectionFailedException(const char* reason_) : reason(reason_) {}
    const char* what() const throw() { return reason; }
    const char* reason;
};

class UnsupportedRequestException : public exception {
   public:
    UnsupportedRequestException(const char* reason_) : reason(reason_) {}
    const char* what() const throw() { return reason; }
    const char* reason;
};

class ResponseException : public exception {
   public:
    ResponseException(const char* reason_) : reason(reason_) {}
    const char* what() const throw() { return reason; }
    const char* reason;
};

class FileRelatedException : public exception {
   public:
    FileRelatedException(const char* reason_) : reason(reason_) {}
    const char* what() const throw() { return reason; }
    const char* reason;
};

#endif
