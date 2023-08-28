#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

struct Info {
    char name[10];
    char number[12];
};

int main(int argc, char* argv[])
{
    if (argc < 2) {
        puts("enter server ip");
        return 0;
    }
    puts("#### PhoneBook 007 Start");
    puts("Phone book client");

    WSADATA wsaData = { 0 };
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        puts("WSAStartup error");
        return 0;
    }

    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        puts("socket creation failed");
        return 0;
    }

    SOCKADDR_IN addr = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_port = htons(11111);
    addr.sin_addr.S_un.S_addr = inet_addr(argv[1]);
    if (connect(sock, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        puts("connect failed");
        printf("%d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 0;
    }

    int cmd = 0;
    char nameBuf[10] = { 0 };
    char numberBuf[12] = { 0 };
    char receiveBuf[128] = { 0 };
    while (true) {
        puts("1. add info\n2.search info\n3.delete info\n4.quit");
        scanf_s("%d", &cmd);

        if (cmd == 1) {
            Info info = { 0 };
            
            puts("\tenter name : ");
            scanf_s("%s", info.name, sizeof(info.name));

            puts("\tenter number : ");
            scanf_s("%s", info.number, sizeof(info.number));

            send(sock, (char*)&info, sizeof(info), 0);
            recv(sock, receiveBuf, sizeof(receiveBuf), 0);
            printf("%s\n", receiveBuf);
        }
        else if (cmd == 2) {

        }
        else if (cmd == 3) {

        }
        else if (cmd == 4) {
            break;
        }
    }

    shutdown(sock, SD_BOTH);
    closesocket(sock);
    WSACleanup();
    return 0;
}

