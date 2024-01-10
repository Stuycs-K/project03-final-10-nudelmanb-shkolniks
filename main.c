#include "main.h"

void err(int i, char*message){
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
    args[2] = "-o";
    args[3] = "StrictHostKeyChecking=no";
    args[4] = "cd Desktop/project03-final-10-nudelmanb-shkolniks;./lab";
    args[5] = NULL;

    printf("%s", sshprompt);
    execvp(args[0], args);
    
    return 0; //0 for functional, yet to add conditions
}

/*Set up the server by creating and binding the socket, and returning the listening socket.
*/
int server_setup() {
  //setup structs for getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; 
  hints->ai_flags = AI_PASSIVE; 
  getaddrinfo(NULL, "58008", hints, &results);
  //create the socket
  int clientd;//store the socket descriptor here
	clientd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);

  //this code should get around the address in use error
  int yes = 1;
  int sockOpt =  setsockopt(clientd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes));
  err(sockOpt, "sockopt error");
  
  //bind the socket to address and port
  bind(clientd, results->ai_addr, results->ai_addrlen);

  err(errno, "check1");
  //set socket to listen state
  listen(clientd, 10);
  err(errno, "check2");

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
  
  return clientd;
}

/*Connect to the client and return the client socket identifier
*/
int server_lab_connect(int listen_socket) {
  int client_socket;

  socklen_t sock_size;
  struct sockaddr_storage client_address;
  sock_size = sizeof(client_address);
  //accept the client connection
  client_socket = accept(listen_socket,(struct sockaddr *) &client_address, &sock_size);

  return client_socket;
}

int main(int argc, char *argv[]){
    int machines = 1;
    int f = 1;
    int current_machine = 0;
    int listen_socket = server_setup();
    err(errno, "check3");

    //set up semaphore
    int semd = semget(SEMKEY, 1, IPC_CREAT | 0644);
    if (semd == - 1) err(errno, "semaphore setup error");

    union semun us;
    us.val = 1;
    int r = semctl(semd, 0, SETVAL, us);

    for(int i=1; i <= machines; i++){
        if(f > 0){
            current_machine = i;
            f = fork();
        }
        else{
            break;
        }
    }
    if(f == 0){
        semd = semget(SEMKEY, 1, 0644);
        if (semd == -1) err(errno, "semaphore 'get' error");

        struct sembuf sb;
        sb.sem_num = 0;
        sb.sem_flg = SEM_UNDO;
        sb.sem_op = -1; //setting operation to down
        semop(semd, &sb, 1);

        int f1 = fork();
        
        if (f1 != 0 ){
            // printf("This is child %d\n", current_machine);
            // err(errno, "check");
            int lab_socket = server_lab_connect(listen_socket);
            printf("got to this point\n");

            sb.sem_op = 1; //setting operation to up
            semop(semd, &sb, 1);
            // char* input_from_client = malloc(BUFFER_SIZE + 1);
            // int bytes = read(lab_socket, input_from_client, BUFFER_SIZE);
            // printf("got here");
            // if(bytes == -1) err(errno, "read error");

            // input_from_client[bytes] = 0;
            // printf("Message: %s\n", input_from_client);
        }
        else if (f1 == 0){
            // printf("machine %d: \n", current_machine);
            // printf("This is child of child %d\n", current_machine);
            lab_run_client("161", current_machine, "bnudelman40");
        }
    }
    return 0;
}