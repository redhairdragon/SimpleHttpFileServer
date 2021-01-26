#include <gtest/gtest.h>

#include <string>

#include "../include/Request.hpp"
TEST(RequestTest, validRequest1) {
    std::string raw =
        "GET /favicon.ico HTTP/1.1\r\nHost: localhost:2000\r\nConnection: "
        "keep-alive\r\n";
    Request r(raw);
    ASSERT_TRUE(r.isSupported());
    ASSERT_EQ(r.getFilePath(), "favicon.ico");
}
TEST(RequestTest, validRequest2) {
    std::string raw =
        "GET /hi/2.jpg HTTP/1.1\r\nHost: localhost:2000\r\nConnection: "
        "keep-alive\r\n";
    Request r(raw);
    ASSERT_TRUE(r.isSupported());
    ASSERT_EQ(r.getFilePath(), "hi/2.jpg");
}

TEST(RequestTest, inValidRequest1) {
    std::string raw = " /favicon.ico GET HTTP/1.1\r\nHost: localhost:2000\r\n";
    Request r(raw);
    ASSERT_FALSE(r.isSupported());
    ASSERT_EQ(r.getFilePath(), "");
}
TEST(RequestTest, inValidRequest2) {
    std::string raw = "randomWords";
    Request r(raw);
    ASSERT_FALSE(r.isSupported());
    ASSERT_EQ(r.getFilePath(), "");
}