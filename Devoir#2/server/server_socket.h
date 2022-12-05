//SIF1015 - Fall 2022
//Made by Julio Bangadebia and Quentin Anière

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "fifo_transactions.c"

#ifndef SERVER_SERVER_SOCKET_H_
#define SERVER_SERVER_SOCKET_H_

#define DEFAULT_PORT 1234
#define MAX_CLIENTS 100

int client_count = 0;
int client_id_count = 0;
int clients[MAX_CLIENTS];

typedef struct ThreadArgs {
    int client_id; //The id of the client
    int socket_fd; //The socket file descriptor of the client
} ThreadArgs;
//This struct is used to pass arguments to the client_handler function

/*
* Listen to client data
* Must be called in a thread
* @param args: a ThreadsArgs struct
*/
void *client_handler(void *client_socket);


/*
* This function is used to listen for new connections.
* it will add any new clients to the clients array.
* @param server_socket the socket to listen on.
* @param port the port to listen on.
*/
void listen_for_clients(int server_socket, int port);

#endif
