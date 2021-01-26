#include "../include/Request.hpp"

#include <iostream>
#include <string>

#include "../include/exceptions.h"
#include "../include/utils.hpp"

Request::Request(const std::string& raw) {
    supported = validate(raw);
    filePath = supported ? parseFilePath(raw) : "";
}

// This only take cares of the 1st line:
// e.g. GET /233.txt HTTP/1.1
// checks the begin and the end
bool Request::validate(const std::string& raw) {
    std::string type = raw.substr(0, 3);
    if (type != "GET") return false;
    bool inValidHttpVersion = (raw.find("HTTP/1.1\r\n") == -1);
    if (inValidHttpVersion) return false;
    return true;
}

// parse only file path
std::string Request::parseFilePath(const std::string& raw) {
    int start = raw.find(" /");
    int end = raw.find("HTTP/1.1\r\n");
    if (start == -1 || end == -1) throw UnsupportedRequestException("");
    return unescape(raw.substr(start + 2, end - start - 2 - 1));
}