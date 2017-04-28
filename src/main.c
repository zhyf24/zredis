//
// Created by zhyf0 on 2017/4/27.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ws2tcpip.h>
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib,"ws2_32.lib")


#define PORT 6379

void main() {

    SOCKET server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(PORT);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(server_sockfd,(struct sockaddr*)&server_sockaddr,sizeof(server_sockaddr))==SOCKET_ERROR){
        printf("套接字绑定到端口失败！端口: %d/n", PORT);
        exit(-1);
    }

    if(listen((SOCKET)server_sockfd, 20) == -1) {
        printf("套接字监听失败！端口: %d/n", PORT);
        exit(-1);
    }

    char buffer[1024];
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);

    SOCKET conn = accept(server_sockfd, (struct sockaddr*)&client_addr, &length);
    if(conn<0) {
        printf("error！端口: %d/n", PORT);
        exit(-1);
    }

    while(1)
    {
        memset(buffer,0,sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer),0);
        if(strcmp(buffer,"exit\n")==0)
            break;
        fputs(buffer, stdout);
        send(conn, buffer, len, 0);
    }

}