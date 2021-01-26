#include <gtest/gtest.h>

#include <fstream>

#include "../include/FileLoader.hpp"
#include "../include/exceptions.h"

TEST(FileLoaderTest, fileNotExists) {
    ASSERT_THROW(FileLoader("notexistfile"), FileRelatedException);
    ASSERT_THROW(FileLoader("notexistfolder/main.cpp2"), FileRelatedException);
}
TEST(FileLoaderTest, fileInPWD) {
    // create test file
    std::string filename("file.txt");
    std::string content = "1234";
    std::ofstream outfile(filename);
    outfile << content;
    outfile.close();

    FileLoader fl(filename);
    ASSERT_EQ(fl.getContentType(), "text/plain");
    ASSERT_EQ(fl.getFileSize(), content.length());
    for (unsigned int i = 0; i < content.length(); ++i)
        ASSERT_EQ(fl.getBytes()[i], content[i]);
    remove(filename.c_str());
}
TEST(FileLoaderTest, fileInFolder) {
    // create test file
    std::string filename("getFileSizeSuccess.txt");
    std::string foldername("testFolder");
    std::string filepath(foldername + "/" + filename);
    std::string content = "1234aaa";

    std::string mkdir = "mkdir -p " + foldername;
    std::string createFile = "echo -n " + content + "> " + filepath;
    system(mkdir.c_str());
    system(createFile.c_str());

    FileLoader fl(filepath);
    ASSERT_EQ(fl.getContentType(), "text/plain");
    ASSERT_EQ(fl.getFileSize(), content.length());
    for (unsigned int i = 0; i < content.length(); ++i)
        ASSERT_EQ(fl.getBytes()[i], content[i]);

    std::string remove = "rm -r " + foldername;
    system(remove.c_str());
}
