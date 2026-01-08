#include <iostream>
#include <WS2tcpip.h>
#include <windows.h>
#include <winsock2.h>
#include <stdio.h>
#include <string>
#include "Client.h"

#pragma comment (lib, "ws2_32.lib");

// g++ Client.cpp -lws2_32 -o client
std::string Client::makeSocket(const std::string& data) {
    WSADATA wsadata;
    int wsaerr;
    wsaerr = WSAStartup(MAKEWORD(2,2), &wsadata);
    if (wsaerr != 0) {
        std::cout << "Winsock dll not found" << std::endl;
        return "";
    } else {
        std::cout << "Winsock DLL Found" << std::endl;
        std::cout << "Status: " << wsadata.szSystemStatus << std::endl;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Error at socket()" << WSAGetLastError() << std::endl;
        WSACleanup();
        return "";
    } else {
        std::cout << "Socket is OK" << std::endl;
    }

    // Client side hint
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(m_port);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    int connResult = connect(clientSocket, (sockaddr*)&addr, sizeof(addr));
    if (connResult == SOCKET_ERROR) {
        std::cerr << "Can't connect to a server, Err: " << WSAGetLastError() << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return "";
    }

    char buff[512];
    int sizeBuff = sizeof(buff);
    ZeroMemory(buff, 512);
    
    int bytes_sent = send(clientSocket, data.c_str(), data.size(), 0);
    if (bytes_sent == SOCKET_ERROR) {
        // If sending fails, print an error
        std::cerr << "send failed: " << WSAGetLastError() << std::endl;
    } else {
        // Print the number of bytes sent
        std::cout << "Sent bytes to the server: [" << bytes_sent << "]" << std::endl;
    }

    int bytesRecv = recv(clientSocket, buff, sizeBuff, 0);
    if (bytesRecv > 0) {
        std::string response(buff, bytesRecv);
        std::cout << "Server response is: [" << response << "]\n";
        std::cout << "Bytes received: [" << bytesRecv << "]\n";

        closesocket(clientSocket);
        WSACleanup();
        return response;

    } else {
        // If no data is received, print an error message
        std::cerr << "recv failed: " << WSAGetLastError() << '\n';
        std::cout << "Server Closed!" << '\n';
    }

    closesocket(clientSocket);
    WSACleanup();
    return "";
}

bool Client::getData(const std::string& data) {
    std::string response { makeSocket(data) };
    
    if (!response.empty()) {
        return true;
    }

    return false;
}

bool Client::sendData(const std::string& data) {
    std::string response { makeSocket(data) };
    
    if (!response.empty()) {
        return true;
    }

    return false;
}

