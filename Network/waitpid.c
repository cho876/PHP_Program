/*
 * waitpid.c
 *
 *  Created on: 2017. 11. 18.
 *      Author: Cho
 */


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
        int status;  // process's dead status
        pid_t pid;  // process's id

        pid = fork();  // Create child process

        if(pid == 0){
                printf("I'm child(1) process\n");
                sleep(5);
                return 1;  // child(1)'s dead status : 1
        }
        else{
                printf("Child(1) process's pid: %d\n", pid);
                while(!waitpid(-1, &status, WNOHANG)){  // If no one died...
                        sleep(1);
                        printf("sleep a seconds...\n");
                }
                if(WIFEXITED(status))
                        printf("died child's status: %d\n", WEXITSTATUS(status));
                printf("Parent End\n");
                return 0;
        }
}
