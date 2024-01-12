#include "networking.h"

/*Connect to the server
 *return the to_server socket descriptor
 *blocks until connection is made.*/
int client_tcp_handshake(char* server_address) {
  //getaddrinfo
  struct addrinfo *hints, *results;
  hints = calloc(1, sizeof(struct addrinfo*));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server

  err(
    getaddrinfo(server_address, PORT, hints, &results) == 0 ? 0 : -1,
    "getaddrinfo error"
  );

  //create the socket
  int clientd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
  err(clientd, "socket error");

  //connect to the server
  int serverd = connect(clientd, results->ai_addr, results->ai_addrlen);
  err(serverd, "connect error");

  free(hints);
  freeaddrinfo(results);

  return clientd;
}

/*Accept a connection from a client
 *return the to_client socket descriptor
 *blocks until connection is made.
 */
int server_tcp_handshake(int listen_socket) {
    //accept the client connection
    struct sockaddr_storage client_address;
    socklen_t sock_size = sizeof(client_address);

    int client_socket = accept(listen_socket, (struct sockaddr*)&client_address, &sock_size);
    err(client_socket, "accept error");
  
    return client_socket;
}

/*Create and bind a socket.
* Place the socket in a listening state.
*/
int server_setup() {
  //setup structs for getaddrinfo
  struct addrinfo *hints, *results;
  hints = calloc(1, sizeof(struct addrinfo*));
  hints->ai_family = AF_INET;
  hints->ai_socktype = SOCK_STREAM; //TCP socket
  hints->ai_flags = AI_PASSIVE; //only needed on server

  err(
    getaddrinfo(NULL, PORT, hints, &results) == 0 ? 0 : -1,
    "getaddrinfo error"
  );

  //create the socket
  int clientd = socket(results->ai_family, results->ai_socktype, results->ai_protocol); //store the socket descriptor here
  err(clientd, "socket error");

  //this code should get around the address in use error
  int yes = 1;
  err(
    setsockopt(clientd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)),
    "sockopt error"
  );
  
  //bind the socket to address and port
  err(
    bind(clientd, results->ai_addr, results->ai_addrlen),
    "bind error"
  );

  //set socket to listen state
  err(
    listen(clientd, 10),
    "listen error"
  );

  //free the structs used by getaddrinfo
  free(hints);
  freeaddrinfo(results);
  
  return clientd;
}

void err(int i, char* message){
  if(i < 0){
	  printf("Error: %s - %s\n", message, strerror(errno));
  	exit(1);
  } else {
    //printf("No error: %s - i=%d\n", message, i);
  }
}
