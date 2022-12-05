#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

#ifndef CLIENT_SOCKET_H
#define CLIENT_SOCKET_H

/*
* This function is used to create a socket and connect to the server.
* @param server_ip: the ip address of the server.
* @param server_port: the port of the server.
* @return: the socket fd.
*/
int connect_to_server(u_int32_t server_ip, int server_port);

/*
* This function is used to get the client ID from the server.
* @param socket_fd: the socket fd.
* @return: the client ID.
*/
int get_client_id(int socket_fd);


void send_transaction(int socket_fd, int client_id, char* operations);

#endif