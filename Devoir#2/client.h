#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef CLIENT_H
#define CLIENT_H

#define DEFAULT_SERVER_PORT 8080
#define DEFAULT_SERVER_IP "127.0.0.1"

/*
* Listen for incoming messages from the server, process them
* and manage ui if needed
* @param *args The socket file descriptor.
* @return void
*/
void server_listenner(void *args);

/*
* Send a message to the server
* @param *args The socket file descriptor.
* @return void
*/
void send_message(void *args);

#endif
