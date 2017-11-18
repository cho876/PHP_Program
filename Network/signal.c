/*
 * signal.c
 *
 *  Created on: 2017. 11. 18.
 *      Author: Cho
 */

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void keycontrol(int sig){
        if(sig == SIGINT)
                printf("CTL+C pressed...\n");
}

void timeout(int sig){
        if(sig == SIGALRM){
                printf("Time Out...\n");
                alarm(2);
        }
}

int main(int argc, char* argv[])
{
        int i;
        signal(SIGALRM, timeout);  // Set alarm function
        signal(SIGINT, keycontrol);  // Set keycontrol function
        alarm(2);  // Alarm function after 2 seconds

        for(i=0; i<5; i++){
                printf("Wait...\n");
                sleep(100); // When signal occurs, initialize
        }
        return 0;
}

