#include "main.h"

/*
This function is used to ssh into a designated the computers in one (or several) StuyCS labs
and download/run an executable file that makes it run like a server and exchange the appropriate
information through the socket. This file should be run on marge other simpson-named machine.
*/
int connect_labs(char* lab, int machine_number){
    char* IP = malloc(14);
    strcpy(IP, "149.90.");
    strcat(IP, lab);
    strcat(IP, ".1");
    if (machine_number < 10){
        strcat(IP, "0");
    }
    char* machine_string = malloc(2);
    sprintf(machine_string, "%d", machine_number);
    strcat(IP, machine_string);

    printf("%s", IP);
    return 0;
}


int main(int argc, char *argv[]){
    connect_labs("150", 15);
}