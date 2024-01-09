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
#include <sys/ipc.h>
#include <sys/sem.h>

#ifndef MAIN_H
#define MAIN_H

#define BUFFER_SIZE 1024
#define SEMKEY 33107

void err(int i, char* message);
int lab_run_client(char* lab, int machine_number, char* user);
int server_lab_connect(int listen_socket);
int server_lab_setup();

union semun { 
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO */
};

#endif