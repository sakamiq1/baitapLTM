// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#pragma warning(disable:4996)

int main(int argc, char* argv[])
{
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    FILE* file;
    FILE* file2;
    file2 = fopen(argv[3], "w");

    char hello[50];

    SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SOCKADDR_IN addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    unsigned short port = (unsigned short)strtoul(argv[1], NULL, 0);

    addr.sin_port = htons(port);

    bind(listener, (SOCKADDR*)&addr, sizeof(addr));

    listen(listener, 5);

    printf("dang cho ket noi \n");

    SOCKET client = accept(listener, NULL, NULL);
    printf("chap nhan ket noi %d\n", client);
    file = fopen(argv[2], "r");
    fscanf(file, "%[^\n]", hello);
    printf("%s\n", hello);
    fclose(file);

    char msg[256];

    int ret = recv(client, msg, sizeof(msg), 0);

    printf("%s", &msg);

    if (ret <= 0)
    {
        printf("Loi ket noi!");
        system("pause");
        return 1;
    }

    fprintf(file2, "%s", msg);
    fclose(file2);

    closesocket(client);
    closesocket(listener);
    WSACleanup();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
