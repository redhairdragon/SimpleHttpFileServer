#include <gtest/gtest.h>

#include <numeric>
#include <vector>

#include "../include/Response.hpp"

TEST(ResponseObjectTest, successResponse) {
    std::string payload = "123";
    std::string expectedHeader = "HTTP/1.1 200 OK\r\nContent-Length:" +
                                 std::to_string(payload.length()) +
                                 std::string("\r\n") +
                                 "Content-Type:application/octet-stream\r\n" +
                                 "Connection: Closed\r\n\r\n";
    Response r(1);
    r.successResponse(payload.c_str(), payload.size(),
                      "application/octet-stream");
    ASSERT_EQ(r.getHeader(), expectedHeader);
    ASSERT_EQ(r.getPayloadPointer(), payload.c_str());
    ASSERT_EQ(r.getPayloadLength(), payload.size());
}

TEST(ResponseObjectTest, badResponse) {
    const std::string BAD_RESPONSE =
        "HTTP/1.0 404 Not Found\r\nContent-Type:text/html\r\nContent-Length:  "
        "12\r\nConnection: close\r\n\r\n<h2>404</h2>";
    char* nullPtr = NULL;
    Response r(1);
    r.badResponse();
    ASSERT_EQ(r.getHeader(), BAD_RESPONSE);
    ASSERT_EQ(r.getPayloadPointer(), nullPtr);
    ASSERT_EQ(r.getPayloadLength(), 0);
}
