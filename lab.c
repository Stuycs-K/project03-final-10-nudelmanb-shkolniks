#include "lab.h"

void err(int i, char*message){
  // if(i < 0){
	  printf("Error: %s - %s\n", message, strerror(errno));
  	// exit(1);
  // }
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
  int error = bind(clientd, results->ai_addr, results->ai_addrlen);
  err(error, "check1.5");

  //set socket to listen state
  int listen_result = listen(clientd, 10);
  err(listen_result, "check2");

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
  printf("got to this part of server_lab_connect");
  //accept the client connection
  client_socket = accept(listen_socket,(struct sockaddr *) &client_address, &sock_size);

  return client_socket;
}

int main(){
    err(0, "check2");
    printf("this is done on the lab machine\n");
    char* IP = "149.89.161.100";
    err(0, "check");

    int listen_socket = server_setup();

    err(0, "check101010");
    server_lab_connect(listen_socket); //the lab machine will run its own server, 
    //to save the client from having to figure out the IP address of the main computer (marge)

    err(0, "check11");
    // int main_socket = connect_to_main(IP);

    // char* input = "howdy";
    // printf("Sending %s to the server\n", input);
    // write(main_socket, input, strlen(input));
    return 0;
}