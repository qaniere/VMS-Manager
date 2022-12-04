#include "server_socket.h"

/*
* This function is used to listen for new connections.
* it will add any new clients to the clients array.
* @param server_socket the socket to listen on.
*/
void listen_for_clients(int server_socket, int port) {

    int listen_result = listen(server_socket, 10);
    if (listen_result == -1) {
        perror("listen");
        exit(1);
    }

    printf("Listening for clients on port %d\n", port);

    while (1) {
        struct sockaddr_in *client_address = malloc(sizeof(struct sockaddr_in));
        socklen_t client_address_size = sizeof(*client_address);
        //Allocate memory for client address

        int client_socket = accept(server_socket, (struct sockaddr *)client_address, &client_address_size);
        if (client_socket == -1) {
            perror("accept error");
            exit(1);
        }

        clients[client_count] = client_socket;
        client_count++;

        int sendable_client_count = htonl(client_count);

        printf("New client connected. ID = %d\n", client_count);
        write(client_socket, &sendable_client_count, sizeof(sendable_client_count)); 
        //Send the client its ID
    }
}
