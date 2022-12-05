//SIF1015 - Fall 2022
//Made by Julio Bangadebia and Quentin Anière

#include "server_socket.h"

FifoTransactions *fifo_head;

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
        //Recreate the transaction sendend by the client because the transaction is not sent as a struct
        //but as a string of characters

        add_transaction(fifo_head, *transaction);
    }
    
    if (bytes == 0) {
        printf("Client %d disconnected\n", client_id);
        close(client_socket);

    } else if (bytes == -1) {
        perror("recv failed");
        close(client_socket);
    }

    
    
    free(thread_args);
    clients[client_id] = -1;
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

    fifo_head = create_fifo_transaction_list();

    pthread_t watch_transactions_thread;
    pthread_create(&watch_transactions_thread, NULL, (void *) watch_transactions, (void *) fifo_head);

    printf("Listening for clients on port %d\n", port);

    for(int i = 0; i < MAX_CLIENTS; i++) {
        clients[i] = -1;
    }

    while (1) {
        struct sockaddr_in *client_address = malloc(sizeof(struct sockaddr_in));
        socklen_t client_address_size = sizeof(*client_address);
        //Allocate memory for client address

        int client_socket = accept(server_socket, (struct sockaddr *)client_address, &client_address_size);
        if (client_socket == -1) {
            perror("accept error");
            exit(1);
        }

        int client_id = assign_client_id();
        clients[client_id] = client_socket;

        if(client_id == -1) {
            printf("Client rejected, server is full\n");
            write(client_socket, "Server is full", 15);
            close(client_socket);
            continue;
        }

        int sendable_client_count = htonl(client_id);

        printf("New client connected. ID = %d\n", client_id);
        write(client_socket, &sendable_client_count, sizeof(sendable_client_count)); 
        //Send the client its ID

        ThreadArgs *args = malloc(sizeof(struct ThreadArgs));
        args->client_id = client_id;
        args->socket_fd = client_socket;

        pthread_t client_thread;
        pthread_create(&client_thread, NULL, (void *) client_handler, (void *) args);        
    }

    for(int i = 0; i < client_count; i++) {
        close(clients[i]);
    }

    close(server_socket);
}

/*
* Check the fifo transactions for any transactions that are ready to be processed and process them.
* @param fifo_head the fifo_head of the fifo transactions.
*/
void *watch_transactions(void *args) {

    FifoTransactions *fifo_head = (FifoTransactions *) args;
    //Cast the args to their correct type

    while (1) {

        if(get_first_transaction(fifo_head) != NULL) {
            Transaction *transaction = get_first_transaction(fifo_head);

            int client_id = transaction->client_id;
            char *operations = transaction->operations;
        
            read_transaction(transaction);

            remove_first_transaction(fifo_head);

        } else {
            sleep(1); //Sleep for 1 second if there are no transactions to process
            //This is to prevent the CPU from being overused
        }
    }
}

/*
* This function goes through the clients array and return the
* first available index. An available index is an index that
* has a value of -1.
* @return the first available index in the clients array.
*/
int assign_client_id() {
    for (int i = 0; i < MAX_CLIENTS; i++) {

        if (clients[i] == -1) {
            return i;
        
        } else if (i == MAX_CLIENTS - 1) {
            printf("Max clients reached\n");
            return -1;
        }
    }
}
