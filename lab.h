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

#ifndef LAB_H
#define LAB_H

#define BUFFER_SIZE 1024
#define SEMKEY 33107

void err(int i, char* message);
int server_setup();
int server_lab_connect(int listen_socket);

#endif