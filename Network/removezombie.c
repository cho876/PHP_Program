/*
 * removezombie.c
 *
 *  Created on: 2017. 11. 18.
 *      Author: Cho
 */


#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void removezombie(int sig){
        if(sig == SIGCHLD){
                int status;  // died child's status
                pid_t pid = waitpid(-1, &status, WNOHANG);
                if(WIFEXITED(status)){  // When child died...
                        printf("Died child's pid: %d\n", pid);
                        printf("Died child's status: %d\n", WEXITSTATUS(status));
                }
        }
}

int main(int argc, char* argv[])
{
        struct sigaction act_rmzombie;
        act_rmzombie.sa_handler = removezombie;
        sigemptyset(&act_rmzombie.sa_mask);
        act_rmzombie.sa_flags = 0;
        sigaction(SIGCHLD, &act_rmzombie, 0);

        pid_t pid;
        pid = fork();
        if(pid == 0){
                printf("I'm child(1) process\n");
                sleep(5);
                return 1;  // child(1)'s status: 1
        }
        else{
                printf("Child(1)'s pid: %d\n", pid);
                pid = fork();
                if(pid == 0){
                        printf("I'm child(2) process\n");
                        sleep(10);
                        return 2;
                }
                else{
                        printf("Child(2)'s pid: %d\n", pid);
                        int i;
                        for(i=0; i<10; i++){  // Wait 20 seconds for the child process to
 die
                                sleep(2);
                                printf("Wait 2 seconds...\n");
                        }
                }
        }
        return 0;
}
