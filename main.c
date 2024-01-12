#include "main.h"

void err(int i, char*message){
    printf("err called for '%s', i=%d, strerror %s\n", message, i, strerror(errno));
   if(i < 0){
	  printf("Error: %s - %s\n", message, strerror(errno));
  	//   exit(1);
   }
}

/*
This function is used to ssh into a designated the computers in one (or several) StuyCS labs
and download/run an executable file that makes it run like a server and exchange the appropriate
information through the socket. This file should be run on marge other simpson-named machine.
*/
int lab_run_client(char* lab, int machine_number, char* user){
    
    char* IP = find_ip(lab, machine_number);

    char* args[16];
    args[0] = "ssh";

    char sshprompt[124];
    strcpy(sshprompt, user);
    strcat(sshprompt, "@");
    strcat(sshprompt, IP);
    args[1] = sshprompt;
    args[2] = "-o";
    args[3] = "StrictHostKeyChecking=no";
    // args[4] = "ls; exit";
    args[4] = "cd Desktop/project03-final-10-nudelmanb-shkolniks;./lab";
    //figure out a way to close connection after the lab is done running
    args[5] = NULL;

    execvp(args[0], args);
    
    return 0; //0 for functional, yet to add conditions
}

char* find_ip(char* lab, int machine_number){
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
    return IP;
}

int connect_machine_net(char* server_address) {
  err(0, "check2");
  //getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; 
  hints->ai_flags = AI_PASSIVE; 
  getaddrinfo(server_address, "58008", hints, &results);

  int clientd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  err(clientd, "child check3");

  int serverd = connect(clientd, results->ai_addr, results->ai_addrlen);
  err(serverd, "connect error");

  free(hints);
  freeaddrinfo(results);

  return clientd;
}

int main(int argc, char *argv[]){
    int machines = 1;
    // int current_machine = 1;
    // int listen_socket = server_setup();
    // err(listen_socket, "check3");

    //set up semaphore
    // int semd = semget(SEMKEY, 1, IPC_CREAT | 0644);
    // if (semd == - 1) err(errno, "semaphore setup error");

    // union semun us;
    // us.val = 1;
    // int r = semctl(semd, 0, SETVAL, us);

    for(int i=1; i <= machines; i++){
        int f = fork();

        err(f, "check4");
        if(f == 0){
            // struct sembuf sb;
            // sb.sem_num = 0;
            // sb.sem_flg = SEM_UNDO;
            // sb.sem_op = -1; //setting operation to down
            // semop(semd, &sb, 1);

            int f1 = fork();
            err(f1, "check5");
            if (f1 == 0){
                printf("this is in the double forked child\n");
                err(f1, "check6");
                // printf("machine %d: \n", current_machine);
                // printf("This is child of child %d\n", current_machine);
                lab_run_client("161", i, "bnudelman40");

                exit(0);
            }  else {
                // printf("This is child %d\n", current_machine);
                err(f1, "check5.5");

                char* lab_IP = find_ip("161", i);
                int lab_socket = connect_machine_net(lab_IP);
                printf("got to this point\n");

                // sb.sem_op = 1; //setting operation to up
                // semop(semd, &sb, 1);
                // char* input_from_client = malloc(BUFFER_SIZE + 1);
                // int bytes = read(lab_socket, input_from_client, BUFFER_SIZE);
                // printf("got here");
                // if(bytes == -1) err(errno, "read error");

                // input_from_client[bytes] = 0;
                // printf("Message: %s\n", input_from_client);

                exit(0);
            }
        }
    }

    return 0;
}