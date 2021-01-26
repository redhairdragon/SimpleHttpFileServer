
project( WebFileServerExample )
cmake_minimum_required( VERSION 3.0 )
set(CMAKE_CXX_STANDARD 11)

find_package(CURL REQUIRED) 
include_directories(${CURL_INCLUDE_DIR})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(include)


add_subdirectory(WebFileServer)

add_executable( ${PROJECT_NAME} main.cpp )
target_link_libraries(${PROJECT_NAME} webfileserver)


FILE(GLOB SC_FILES "tests/*.cpp")

add_executable("${PROJECT_NAME}Test" test.cpp ${SC_FILES})
target_link_libraries("${PROJECT_NAME}Test" 
    ${GTEST_BOTH_LIBRARIES} 
    ${CMAKE_THREAD_LIBS_INIT} 
    fileloader 
    response
    request
    utils)
add_test(Test "${PROJECT_NAME}Test")
enable_testing()