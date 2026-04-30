#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {

    // Step 1: declare the socket
    int client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    // Step 2: define the address of the server socket we want to connect to 
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET; // sets to IPv4
    server_address.sin_port = htons(5100); // sets the port to 5100
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // sets IP address to 0.0.0.0
    // Step 3: connect to the socket
    if (connect(client_socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
	perror("connect()");
	exit(EXIT_FAILURE);
    }
    // Step 4: read and write 

    return 0;
}
