/*
 * multi_echo_server.c
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
#include <signal.h>

#define BUF_SIZE 32

void error_handling(char* msg);
void remove_process(int sig);


int main(int argc, char* argv[]){
        char msg[BUF_SIZE];
        int str_len;

        pid_t pid;  // Process's id
        int serv_sock, clnt_sock;  // server & client's socket fd
        struct sockaddr_in serv_addr, clnt_addr;  // server & client's socket's info
        socklen_t clnt_addr_size;

        //  sigaction initialize
        struct sigaction ack;
        ack.sa_handler = remove_process;
        sigemptyset(&ack.sa_mask);
        ack.sa_flags = 0;

        if(argc != 2)
                error_handling("argc ERROR");

        serv_sock = socket(PF_INET, SOCK_STREAM, 0);
        if(serv_sock == -1)
                error_handling("socket() ERROR");

        // Set server's info
        memset(&serv_addr, 0, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
        serv_addr.sin_port = htons(atoi(argv[1]));

        if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1)
                error_handling("bind() ERROR");
        if(listen(serv_sock, 5) == -1)
                error_handling("listen() ERROR");

        while(1){
                clnt_addr_size = sizeof(clnt_addr);
                clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
                pid = fork(); // Duplicate process
                if(pid == 0){
                        close(serv_sock);
                        while((str_len = read(clnt_sock, msg, BUF_SIZE)) != 0)
                                write(clnt_sock, msg, str_len);
                        close(clnt_sock);
                        return 0;
                }
                else
                        close(clnt_sock);
        }
        close(serv_sock);
        return 0;
}

void remove_process(int sig){
        if(sig == SIGCHLD){
                int status;  // process's status
                pid_t pid = waitpid(-1, &status, WNOHANG);
                if(WIFEXITED(status)){
                        printf("Died process's pid: %d\n", pid);
                        printf("Died process's status: %d\n", status);
                }
        }
}

void error_handling(char* msg){
        fputs(msg, stderr);
        fputc('\n', stderr);
        exit(1);
}

