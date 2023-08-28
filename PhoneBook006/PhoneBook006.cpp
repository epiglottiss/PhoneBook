
#include <iostream>
#include <string.h>
#include <winsock2.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

enum ReuestType {
    ADD_INFO = 1,
    FIND_INFO =2,
};

struct Info {
    char name[10];
    char number[12];
};

struct Node {
    std::string name;
    std::string number;
    Node* next;
};

Node pool[1100000];
int poolIdx;

Node* head;

Node* newNode() {
    return &pool[poolIdx++];
}

void addInfo(Info* info) {
    Node* node = newNode();
    node->name = info->name;
    node->number = info->number;
    node->next = head;

    head = node;
}

int main()
{
    puts("#### PhoneBook006 start");
    puts("Phone book Server Start");

    WSADATA wsaData = { 0 };
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        puts("WSASatrtup Error.");
        return 0;
    }
    puts("WSAStartup");

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        puts("Socket Create Failed");
        return 0;
    }
    puts("Server Socket Created");

    SOCKADDR_IN addrInfo;
    addrInfo.sin_family = AF_INET;
    addrInfo.sin_port = htons(11111);
    addrInfo.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
    if(bind(sock, (SOCKADDR*)&addrInfo, sizeof(addrInfo)) == SOCKET_ERROR) {
        puts("bind failed");
        printf("%d\n", WSAGetLastError());
        return 0;
    }
    puts("bind");

    if (listen(sock, SOMAXCONN) == SOCKET_ERROR) {
        puts("listen failed");
        return 0;
    }
    puts("listen");

    SOCKADDR_IN clientAddr = { 0 };
    int clientAddrLen = sizeof(clientAddr);
    SOCKET clientSocket = 0;
    Info receivedInfo = { 0 };
    int receivedBytes = 0;
    const char* retMsg = "saved";

    while (true) {
        clientSocket = accept(sock, (SOCKADDR*)&clientAddr, &clientAddrLen);
        if (clientSocket == INVALID_SOCKET) {
            puts("accept failed");
            printf("%d\n", WSAGetLastError());
            break;
        }
        puts("new connection");

        while (receivedBytes = recv(clientSocket, (char*)&receivedInfo, sizeof(receivedInfo), 0)) {
            addInfo(&receivedInfo);
            send(clientSocket, retMsg, sizeof(retMsg), 0);
            puts(retMsg);
        }

        shutdown(clientSocket, SD_BOTH);
        closesocket(clientSocket);
        puts("disconected");
    }
    puts("server close");
    closesocket(sock);

    WSACleanup();
    return 0;
}


