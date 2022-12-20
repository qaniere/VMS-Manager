//SIF1015 - Fall 2022
//Made by Julio Bangadebia and Quentin Anière

#include "server.h"


int main(int argc, char *argv[]) {

    int port;
    if(argc != 2) {
        port = DEFAULT_PORT;

    } else {
        port = atoi(argv[1]);
    }

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket");
        exit(1);
    }

    struct sockaddr_in *server_address = malloc(sizeof(struct sockaddr_in));

    server_address->sin_family = AF_INET; //IPv4
    server_address->sin_port = htons(port); //The port to listen on
    server_address->sin_addr.s_addr = htonl(INADDR_ANY); //Any IP address (0.0.0.0/0)
    //Set the server infos in the server_address structure

    int bind_result = bind(server_socket, (struct sockaddr *) server_address, sizeof(struct sockaddr_in));
    if (bind_result == -1) {
        perror("bind error");
        exit(1);
    }

    listen_for_clients(server_socket, port);

    close(server_socket);
    return 0;
}
