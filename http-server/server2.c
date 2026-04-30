#include <stdio.h> //common C utils
#include <stdlib.h> //other common C utils
#include <sys/types.h> // common types
#include <sys/socket.h> // socket utils
#include <unistd.h> // unix api
#include <netinet/in.h> // protocol utils

int main(){
    // Step 1: create socket
    int server_socket;
    // Note: SOCK_STREAM = TCP connection
    server_socket = socket(AF_INET, SOCK_STREAM, 0); // returns the File Descriptor(FD) for the new socket
    if (server_socket < 0) {
	perror("network_socket");
	exit(EXIT_FAILURE);
    }

    // Step 2: give address and port to socket
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET; // IPv4
    server_address.sin_port = htons(9002); // converts to network byte order
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr*)&server_socket, sizeof(server_socket)) < 0) {
	perror("bind");
	exit(EXIT_FAILURE);
    }
    
    // Step 3: listen to socket for incoming connections
    listen(server_socket, 5); // 5 is the number of clients that can wait in the queue

    // Step 4: accept the incoming connection
    int client_socket = accept(server_socket, NULL, NULL);

    // Step 5: send message!
    char server_message[256] = "You reached the server!";
    send(client_socket, server_message, sizeof(server_message), 0);
  return 0;
}
