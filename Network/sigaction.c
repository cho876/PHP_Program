/*
 * sigaction.c
 *
 *  Created on: 2017. 11. 18.
 *      Author: Cho
 */


#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig){
        if(sig == SIGALRM){
                printf("Time Out!!!\n");
                alarm(2);
        }
}

void keycontrol(int sig){
        if(sig == SIGINT)
                printf("CTL+C Pressed!!!\n");
}

int main(int argc, char* argv[])
{
        int i;
        struct sigaction act_time, act_key;

        act_time.sa_handler = timeout;
        act_key.sa_handler = keycontrol;

        sigemptyset(&act_time.sa_mask);
        sigemptyset(&act_key.sa_mask);

        act_time.sa_flags = 0;
        act_time.sa_flags = 0;

        sigaction(SIGALRM, &act_time, 0);  // Set Alarm function
        sigaction(SIGINT, &act_key, 0);  // Set Keyboard function

        alarm(2); // Alarm function after 2 Seconds...

        for(i=0; i<5; i++){
                printf("Wait...\n");
                sleep(100); // When signal occurs, initialize
        }
        return 0;
}
