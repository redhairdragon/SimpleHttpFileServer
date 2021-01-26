#include <iostream>

#include "./include/WebFileServer.hpp"
#include "./include/exceptions.h"
unsigned short get_portno(int* argc, char** argv[]);

int main(int argc, char* argv[]) {
    try {
        unsigned short portno = get_portno(&argc, &argv);
        WebFileServer wfs(portno, 1000, 1);
        wfs.start();

    } catch (const SocketsInitFailedException& e) {
        std::cerr << "SocketsInitFailedException: " << e.what() << std::endl;
        return -1;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return -2;
    }
    return 0;
}

// potential short-int conversion overflow here
unsigned short get_portno(int* argc, char** argv[]) {
    if ((*argc) < 2) return 80;
    int portno = atoi((*argv)[1]);
    return portno;
}