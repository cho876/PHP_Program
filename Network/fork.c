#include <stdio.h>
#include <unistd.h>

int gval = 20;  // Global variable

int main(int argc, char* argv[]){
        pid_t pid; // process ID
        int lval = 10; // Local variable

        pid = fork(); // Create child process

        if(pid == 0){
                printf("I'm child process\n");
                gval += 1, lval += 1;
                printf("Child gval: %d, lval: %d\n", gval, lval);
        }
        else{
                printf("I'm parent process\n");
                printf("Child process pid: %d\n", pid);
                gval -= 1, lval -= 1;
                printf("Parent gval: %d, lval: %d\n", gval, lval);
        }
        return 0;
}
