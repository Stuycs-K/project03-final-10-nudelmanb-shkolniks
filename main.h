#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h> 
#include <netdb.h>

#ifndef MAIN_H
#define MAIN_H

#define BUFFER_SIZE 1024

void err(); //may add with parameters
int connect_labs(char* lab, int machine_number, char* user);
int server_lab_connect();

#endif