#include <gtest/gtest.h>
#include <stdio.h>

#include <fstream>
#include <iostream>

#include "../include/exceptions.h"
#include "../include/utils.hpp"

TEST(getFileSize, success) {
    // create test file
    std::string filename("getFileSizeSuccess.txt");
    std::string content = "1234";
    std::ofstream outfile(filename);
    outfile << content;
    outfile.close();

    long result = get_file_size(filename);
    ASSERT_EQ(content.length(), result);
    remove(filename.c_str());
}

TEST(getFileSize, fileNotExists) {
    ASSERT_THROW(get_file_size("weirdFileName"), FileRelatedException);
}

TEST(loweredString, success) { ASSERT_EQ(lowered_string("Abc"), "abc"); }

TEST(getFileExtension, general) {
    ASSERT_EQ("", get_file_extension("a"));
    ASSERT_EQ("jpg", get_file_extension("x.jpg"));
    ASSERT_EQ("jpg", get_file_extension("/23/x.jpg"));
    ASSERT_EQ("jpg", get_file_extension("6/x.jpg"));
    ASSERT_EQ("txt", get_file_extension("6/x.txt"));
    ASSERT_EQ("out", get_file_extension("x.out"));
}
TEST(getFileType, general) {
    ASSERT_EQ("image/jpeg", get_file_type("a.jpg"));
    ASSERT_EQ("text/plain", get_file_type("a.txt"));
    ASSERT_EQ("image/gif", get_file_type("a.gif"));
    ASSERT_EQ("image/jpeg", get_file_type("a.jpeg"));
    ASSERT_EQ("text/html", get_file_type("a.html"));
    ASSERT_EQ("text/html", get_file_type("a.htm"));
    ASSERT_EQ("application/octet-stream", get_file_type("a"));
    // under folder
    ASSERT_EQ("image/jpeg", get_file_type("a/a.jpg"));
    ASSERT_EQ("image/jpeg", get_file_type("c/a/a.jpg"));
    ASSERT_EQ("application/octet-stream", get_file_type("d/a"));
}
TEST(unescapeTest, general) {
    ASSERT_EQ(unescape("abc%20d"), "abc d");
    ASSERT_EQ(unescape("%223%22"), "\"3\"");
    ASSERT_EQ(unescape("%26%22%21ac"), "&\"!ac");
}
