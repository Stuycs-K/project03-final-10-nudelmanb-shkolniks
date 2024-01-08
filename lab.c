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

int connect_to_main(char* server_address) {

  //getaddrinfo
  struct addrinfo * hints, * results;
  hints = calloc(1,sizeof(struct addrinfo));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; 
  hints->ai_flags = AI_PASSIVE; 
  getaddrinfo(server_address, "1738", hints, &results);

  int serverd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  //use bind
  bind(serverd, results->ai_addr, results->ai_addrlen);
  
  //connect to the server
  connect(serverd, results->ai_addr, results->ai_addrlen);

  free(hints);
  freeaddrinfo(results);

  return serverd;
}

int main(){
    printf("this is done on the lab machine\n");
    char* IP = "149.89.161.100";
    int main_socket = connect_to_main(IP);

    char* input = "howdy";
    printf("Sending %s to the server\n", input);
    write(main_socket, input, strlen(input));

    return 0;
}