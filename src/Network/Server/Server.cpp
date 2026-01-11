#include <iostream>
#include <WS2tcpip.h>
#include <windows.h>
#include <winsock2.h>
#include <stdio.h>
#include <string>

#pragma comment (lib, "ws2_32.lib");

int start() {
    WSADATA wsadata;
    int wsaerr;
    wsaerr = WSAStartup(MAKEWORD(2, 2), &wsadata);
    if (wsaerr != 0) {
        std::cout << "Winsock dll not found" << std::endl;
        return 1;
    } else {
        // std::cout << "winsock DLL Found" << std::endl;
        // std::cout << "Status: " << wsadata.szSystemStatus << std::endl;
    }

    SOCKET in = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (in == INVALID_SOCKET) {
        std::cout << "Error at socket()" << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    } else {
        // std::cout << "Socket is OK" << std::endl;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
    addr.sin_addr.S_un.S_addr = ADDR_ANY;

    if (bind(in, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cout << "Can't bind socket! " << WSAGetLastError() << std::endl;
		WSACleanup();
        return 1;
    }

    while(true) {
        break;
    }

    WSACleanup();
    return 1;
}