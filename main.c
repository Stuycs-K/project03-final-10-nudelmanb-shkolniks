#include "main.h"

void err(){
    printf("errno %d\n", errno);
    printf("%s\n", strerror(errno));
    // exit(1);
}

/*
This function is used to ssh into a designated the computers in one (or several) StuyCS labs
and download/run an executable file that makes it run like a server and exchange the appropriate
information through the socket. This file should be run on marge other simpson-named machine.
*/
int connect_labs(char* lab, int machine_number, char* user){
    char* IP = malloc(14);
    strcpy(IP, "149.89.");
    strcat(IP, lab);
    strcat(IP, ".1");
    if (machine_number < 10){
        strcat(IP, "0");
    }
    char* machine_string = malloc(2);
    sprintf(machine_string, "%d", machine_number);
    strcat(IP, machine_string);

    char* args[16];
    args[0] = "ssh";

    char sshprompt[124];
    strcpy(sshprompt, user);
    strcat(sshprompt, "@");
    strcat(sshprompt, IP);

    args[1] = sshprompt;
    args[2] = "cd Desktop/project03-final-10-nudelmanb-shkolniks;./lab";
    args[3] = NULL;

    printf("%s", sshprompt);
    execvp(args[0], args);
    
    return 0; //0 for functional, yet to add conditions
}


int main(int argc, char *argv[]){
    connect_labs("161", 1, "bnudelman40");
}