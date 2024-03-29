//SIF1015 - Fall 2022
//Made by Julio Bangadebia and Quentin Anière

#include "client_socket.h"

/*
* This function is used to connect to a server.
* @param server_address the address of the server to connect to.
* @param port the port to connect to.
* @return the socket used to communicate with the server.
*/
int connect_to_server(u_int32_t server_address, int port) {

    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("socket creation error");
        exit(1);
    }

    struct sockaddr_in *server_infos = malloc(sizeof(struct sockaddr_in));
    server_infos->sin_family = AF_INET; //IPv4
    server_infos->sin_port = htons(port); //The port to listen on
    server_infos->sin_addr.s_addr = server_address; //The address to connect
    //Create a struct to store the server address

    int connect_result = connect(client_socket, (struct sockaddr *) server_infos, sizeof(struct sockaddr_in));
    if (connect_result == -1) {
        perror("connect error");
        exit(1);
    }

    return client_socket;
}

/*
* This function is used to get the client ID from the server.
* @param socket_fd: the socket fd.
* @return: the client ID.
*/
int get_client_id(int socket_fd) {
    
    int received_id = 0;
    int read_result = read(socket_fd, &received_id, sizeof(int));
    if (read_result == -1) {
        perror("read error");
        exit(1);
    }

    return ntohl(received_id); //Convert the received ID to host byte order (big or little endian)
}

/*
* This function is used to send the client transaction to the server.
* @param socket_fd: the socket fd of the client.
* @param client_id: the client ID (given by the server).
* @param transaction: the string of operations.
*/
void send_transaction(int socket_fd, int client_id, char *operations) {

    char *transaction_string = malloc((TRANSACTION_MAX_SIZE * sizeof(char)) + sizeof(client_id));
    sprintf(transaction_string, "%d/%s", client_id, operations);
    //Transaction string is now "client_id/operations"

    int write_result = write(socket_fd, transaction_string, strlen(transaction_string) * sizeof(char));
    if (write_result == -1) {
        perror("write error");
        exit(1);
    }

    for(int i = 0; i < TRANSACTION_MAX_SIZE; i++) {
        operations[i] = '\0';
    }

    free(transaction_string);
}
