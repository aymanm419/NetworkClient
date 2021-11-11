#ifndef NETWORKSERVER_SERVER_H
#define NETWORKSERVER_SERVER_H

#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iostream>
#include <string>
#include "Socket.h"
#include <thread>
#include <chrono>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
using namespace std::chrono_literals;

class Client {

public:
    Client(std::string ip, std::string port);

    Socket *getConnection();

    void handleSocket(Socket *socket);

    static void destroy();
    SOCKET connectSocket = INVALID_SOCKET;
private:
    static bool readyToReceive(Socket* socket);

};


#endif //NETWORKSERVER_SERVER_H
