//SIF1015 - Fall 2022
//Made by Julio Bangadebia and Quentin Anière

#include "server_socket.h"

FifoTransactions *head;

/*
* Listen to client data
* Must be called in a thread
* @param args: a ThreadsArgs struct
*/
void *client_handler(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *) args;
    int client_socket = thread_args->socket_fd;
    int client_id = thread_args->client_id;
    //Cast the args to their correct type
    
    int bytes;
    char buffer[1024];

    while ((bytes = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        printf("Client %d: %s\n", client_id, buffer);

        Transaction *transaction = malloc(sizeof(Transaction));
        transaction->client_id = client_id;
        strcpy(transaction->operations, buffer);

        add_transaction(head, *transaction);
    }
    
    if (bytes == 0) {
        printf("Client %d disconnected\n", client_id);
        close(client_socket);

    } else if (bytes == -1) {
        perror("recv failed");
        close(client_socket);
    }

    
    
    free(thread_args);
    client_count--;
    return 0;
}

/*
* This function is used to listen for new connections.
* it will add any new clients to the clients array.
* @param server_socket the socket to listen on.
* @param port the port to listen on.
*/
void listen_for_clients(int server_socket, int port) {

    int listen_result = listen(server_socket, 10);
    if (listen_result == -1) {
        perror("listen errror");
        exit(1);
    }

    head = malloc(sizeof(FifoTransactions));
    head->next = NULL;
    head->transaction = NULL;

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
        client_id_count++;
        //The count is the capacity of the array, the id is the client id

        int sendable_client_count = htonl(client_id_count);

        printf("New client connected. ID = %d\n", client_id_count);
        write(client_socket, &sendable_client_count, sizeof(sendable_client_count)); 
        //Send the client its ID

        ThreadArgs *args = malloc(sizeof(struct ThreadArgs));
        args->client_id = client_count;
        args->socket_fd = client_socket;

        pthread_t client_thread;
        pthread_create(&client_thread, NULL, (void *) client_handler, (void *) args);        
    }

    for(int i = 0; i < client_count; i++) {
        close(clients[i]);
    }

    close(server_socket);
}
