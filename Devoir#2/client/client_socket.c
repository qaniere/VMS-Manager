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
        perror("socket");
        exit(1);
    }

    struct sockaddr_in *server_infos = malloc(sizeof(struct sockaddr_in));

    server_infos->sin_family = AF_INET; //IPv4
    server_infos->sin_port = htons(port); //The port to listen on
    server_infos->sin_addr.s_addr = server_address; //The address to connect<

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
    
        char *buffer = malloc(sizeof(char) * 10);
        int read_result = read(socket_fd, buffer, 10);
        if (read_result == -1) {
            perror("read error");
            exit(1);
        }
    
        int client_id = atoi(buffer);
        free(buffer);
    
        return client_id;
}