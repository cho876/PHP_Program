/*
 * wait.c
 *
 *  Created on: 2017. 11. 18.
 *      Author: Cho
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
        int status;   // child's status
        pid_t pid;  // process pid

        pid = fork();  // Create child process

        if(pid == 0){
                printf("I'm child(1) process\n");
                sleep(3);
                return 1;  // child(1)'s dead status : 1
        }
        else{
                printf("Child(1)'s pid: %d\n", pid);
                pid = fork();  // Create child process

                if(pid == 0){
                        printf("I'm child(2) process\n");
                        sleep(6);
                        return 2;  // child(2)'s dead status: 2
                }
                else{
                        printf("Child(2)'s pid: %d\n", pid);
                        wait(&status);
                        if(WIFEXITED(status))
                                printf("Dead process status: %d\n", WEXITSTATUS(status));
                        wait(&status);
                        if(WIFEXITED(status))
                                printf("Dead process status: %d\n", WEXITSTATUS(status));
                }
        }
        return 0;
}

