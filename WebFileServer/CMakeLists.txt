find_package( Threads REQUIRED)
add_library(utils "utils.cpp")
target_link_libraries(utils ${CURL_LIBRARIES})

add_library(response "Response.cpp")
target_link_libraries(response utils)

add_library(request "Request.cpp")
target_link_libraries(request  utils)
add_library(fileloader "FileLoader.cpp")

add_library(webfileserver "WebFileServer.cpp")
target_link_libraries(webfileserver request response fileloader Threads::Threads)