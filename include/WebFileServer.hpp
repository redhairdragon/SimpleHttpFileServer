#ifndef WEBFILESERVER_H
#define WEBFILESERVER_H
#include <netinet/in.h>  // constants and structures needed for internet domain addresses, e.g. sockaddr_in

#include <string>
class WebFileServer {
   public:
    WebFileServer(unsigned short portno = 80, unsigned max_connections = 100,
                  bool verbose = false);
    ~WebFileServer();
    void start();

   private:
    int getClientSocketFd();
    std::string getRawRequest(int clientSocketFd);
    void generate_response();

    // socket related variables
    int hostSocketFd;
    struct sockaddr_in cli_addr, serv_addr;
    socklen_t clilen;

    bool verbose;
};
#endif
