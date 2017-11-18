/*
 * multi_echo_client.c
 *
 *  Created on: 2017. 11. 18.
 *      Author: Cho
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 32

void error_handling(char* msg);
void read_routine(int sock, char* msg);
void write_routine(int sock, char* msg);

int main(int argc, char* argv[])
{
        pid_t pid;

        int sock;
        struct sockaddr_in serv_addr;
        socklen_t serv_addr_size;
        char msg[BUF_SIZE];

        if(argc != 3)
                error_handling("argc ERROR");

        sock = socket(PF_INET, SOCK_STREAM, 0);
        if(sock == -1)
                error_handling("socket() ERROR");

        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
        serv_addr.sin_port = htons(atoi(argv[2]));

        if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
                error_handling("connect() ERROR");
        else
                printf("Connected...\n");

        pid = fork();  // Duplicate process
        if(pid == 0)
                write_routine(sock, msg);
        else
                read_routine(sock, msg);

        return 0;
}

void write_routine(int sock, char* msg){
        while(1){
                fgets(msg, BUF_SIZE, stdin);

                if(!strcmp(msg, "q\n") || !strcmp(msg, "Q\n")){
                        shutdown(sock, SHUT_WR);
                        return;
                }
                write(sock, msg, strlen(msg));
        }
}

void read_routine(int sock, char* msg){
        while(1){
                int str_len;
                str_len = read(sock, msg, BUF_SIZE);
                if(str_len == 0)
                        return;
                msg[str_len] = 0;
                printf("돌아온 메세지: %s\n", msg);
        }
}
void error_handling(char* msg){
        fputs(msg, stderr);
        fputc('\n', stderr);
        exit(1);
}
