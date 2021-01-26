#include "../include/WebFileServer.hpp"

#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <sstream>
#include <thread>

#include "../include/FileLoader.hpp"
#include "../include/Request.hpp"
#include "../include/Response.hpp"
#include "../include/exceptions.h"

WebFileServer::WebFileServer(unsigned short portno, unsigned max_connections,
                             bool verbose)
    : verbose(verbose) {
    memset((char *)&serv_addr, 0, sizeof(serv_addr));

    // fill in address info
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    // create socket
    hostSocketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (hostSocketFd < 0)
        throw SocketsInitFailedException("Cannot get socket fd");

    // bind socket
    if (::bind(hostSocketFd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <
        0)
        throw SocketsInitFailedException("Cannot bind socket");
    listen(hostSocketFd, max_connections);
}

WebFileServer::~WebFileServer() { close(hostSocketFd); }

bool is_request_end(const string &request) {
    if (request.length() > 4)
        if (request.substr(request.length() - 4) == "\r\n\r\n") return true;
    return false;
}

int WebFileServer::getClientSocketFd() {
    int clientSocketFd =
        accept(hostSocketFd, (struct sockaddr *)&cli_addr, &clilen);
    if (clientSocketFd < 0)
        throw new ConnectionFailedException("ERROR on accept");
    return clientSocketFd;
}

std::string WebFileServer::getRawRequest(int clientSocketFd) {
    const unsigned BUFFER_SIZE = 256;
    int n = 1;
    string request("");
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);

    // read client's message
    while (n > 0) {
        n = read(clientSocketFd, buffer, BUFFER_SIZE);
        if (n < 0)
            throw new ConnectionFailedException("ERROR reading from socket");
        request += string(buffer);
        memset(buffer, 0, BUFFER_SIZE);
        if (is_request_end(request)) break;
    }
    if (verbose) std::cout << request;
    return request;
}

void WebFileServer::start() {
    using std::string;

    while (1) {
        // accept connections
        int clientSocketFd = getClientSocketFd();

        std::thread worker{[clientSocketFd, this]() {
            Response response(clientSocketFd);
            try {
                string rawRequest = getRawRequest(clientSocketFd);
                Request request(rawRequest);
                if (request.isSupported()) {
                    string filepath = request.getFilePath();
                    FileLoader fileloader = FileLoader(filepath);
                    response.successResponse(fileloader.getBytes(),
                                             fileloader.getFileSize(),
                                             fileloader.getContentType());
                    response.send();
                } else {
                    response.badResponse();
                    response.send();
                }
            } catch (const std::exception &e) {
                std::cerr << e.what() << std::endl;
            }
            close(clientSocketFd);  // close connection
        }};
        worker.detach();
    }
}