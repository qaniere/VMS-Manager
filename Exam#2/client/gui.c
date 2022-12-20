//SIF1015 - Fall 2022
//Made by Quentin Anière

#include "gui.h"

int lines, columns;
//Contains LINES and COLS from ncurses.h

int client_id = 7;
//Contains the number of the selected VMS

char server_ip[16] = " ";
//Contains the IP of the server in a string

WINDOW *windows[2] = {NULL, NULL};
//Contains the two windows [0] is the left window, [1] is the right window

Transaction *transaction = NULL;
//The current transaction that will be sent to the server

int socket_fd = -1;
//Contains the socket fd

/*
* This function initializes the ncurses library and creates two windows
*/
void init_gui() {
    initscr(); 
    //Initialize ncurses library
    
    keypad(stdscr, TRUE);
    //Enable keyboard input

    curs_set(0);
    //Hide cursor

    lines = LINES;
    columns = COLS;
    
    WINDOW *left_window = newwin(lines, columns / 2, 0, 0);
    WINDOW *right_window = newwin(lines, columns / 2, 0, (columns / 2) -1);
    refresh();
    //Create two windows

    windows[0] = left_window;
    windows[1] = right_window;

    box(left_window, 0, 0);
    box(right_window, 0, 0);

    mvwprintw(left_window, 0, 2, "Transmission");
    mvwprintw(right_window, 0, 2, "Reception");
    //Title of the windows

    int middle = ((columns / 2) - 1) / 2;

    char firstLine[] = "Saisissez le nom du fichier";
    char secondLine[] = "dont vous voulez recuperer les informations";
    char thirdLine[] = "et appuyez sur \"entree\"";
    char fourthLine[] = "ou \"q\" pour quitter";

    mvwprintw(windows[0], 2, middle - (strlen(firstLine) / 2), firstLine);
    mvwprintw(windows[0], 3, middle - (strlen(secondLine) / 2), secondLine);
    mvwprintw(windows[0], 4, middle - (strlen(thirdLine) / 2), thirdLine);
    mvwprintw(windows[0], 5, middle - (strlen(fourthLine) / 2), fourthLine);

    mvwprintw(windows[0], 7, 2, "> ");

    wrefresh(left_window);
    wrefresh(right_window);
    //Refresh windows

    display_server_ip();
    display_client_id();
    refresh();
}

/*
* This function is a loop that make the GUI update and wait for user input
*/
void gui_loop() {
    while(1) {

        display_client_id();
        display_server_ip();
        //Display the client ID and the server IP

        wrefresh(windows[0]);
        wrefresh(windows[1]);
        //Refresh windows

        if(transaction == NULL) {
            transaction = malloc(sizeof(Transaction));
            transaction->clientID = client_id;
        }

        mvwprintw(windows[0], 7, 2, "> ");

        char filename[256];
        mvgetnstr(7, 5, filename, 256);
        //Get the user input

        if(filename[0] == 'q' || filename[0] == 'Q' || filename == "quit") {
            break;

        } else {
            char operation[256];
            sprintf(operation, "S %s", filename);
            //Create the operation string 
            //The operation string is in the form of "S <filename>"

            addOperationToTransaction(transaction, operation);
            send_transaction(socket_fd, client_id, transaction->operations);
            //Send the transaction to the server

            transaction->operations[0] = '\0';
            transaction = NULL;
            //Reset the transaction

            mvwprintw(windows[0], 7, 2, "                        ");
            mvwprintw(windows[0], 7, 2, "> ");
            wrefresh(windows[0]);
            //Clear the input

            redisplay_everything();
        }

        refresh();
    }
}

/*
* This function destroys the window and ends the ncurses library
*/
void gui_cleanup() {
    endwin();
}

/*
* This function display the server ip the bottom of the left window
*/
void display_server_ip() {

    mvwprintw(windows[0], lines - 2, 2, "                        ");
    //Clear the previous text

    char real_server_ip[16] = "";
    if(server_ip[0] == ' ') {
        strcpy(real_server_ip, "Not connected");

    } else {
        strcpy(real_server_ip, server_ip);
    } 

    mvwprintw(windows[0], lines - 2, 2, "Server IP: %s", real_server_ip);
    wrefresh(windows[0]);
}

/*
* This function update the server_ip global variable
* @param ip The new server ip
*/
void update_server_ip(char *ip) {
    sprintf(server_ip, "%s", ip);
} 


/*
* This function display the client id in the bottom of the left window
*/
void display_client_id() {
    mvwprintw(windows[0], lines - 3, 2, "                        ");
    //Clear the previous text

    if(client_id == -1) {
        mvwprintw(windows[0], lines - 3, 2, "Client ID: None");
        wrefresh(windows[0]);

    } else {
        mvwprintw(windows[0], lines - 3, 2, "Client ID: %d", client_id);
        wrefresh(windows[0]);
    }
}


/*
* This function redisplay everything, the menu, the cursor the client id, the server ip and
* the windows border. This function is meant to be used when a popup is closed
*/
void redisplay_everything() {
    display_server_ip();
    display_client_id();

    box(windows[0], 0, 0);
    box(windows[1], 0, 0);

    mvwprintw(windows[0], 0, 2, "Transmission");
    mvwprintw(windows[1], 0, 2, "Reception");

    int middle = ((columns / 2) - 1) / 2;

    char firstLine[] = "Saisissez le nom du fichier";
    char secondLine[] = "dont vous voulez recuperer les informations";
    char thirdLine[] = "et appuyez sur \"entree\"";

    mvwprintw(windows[0], 2, middle - (strlen(firstLine) / 2), firstLine);
    mvwprintw(windows[0], 3, middle - (strlen(secondLine) / 2), secondLine);
    mvwprintw(windows[0], 4, middle - (strlen(thirdLine) / 2), thirdLine);

    refresh();
    wrefresh(windows[0]);
    wrefresh(windows[1]);
}

/*
* Update the client id global var
* @param id The new client id
*/
void update_client_id(int id) {
    client_id = id;
}

/*
* Update the socket fd global var
* @param fd The new socket fd
*/
void update_socket_fd(int fd) {
    socket_fd = fd;
}

/*
* This function listen for the server and display any received message in the right window
* @param socket The socket to listen on
*/
void *server_listenner(void *socket) {

    int client_socket = *(int *)socket;
    //Cast the arg to their correct type

    int bytes;
    char buffer[1024];
    while(bytes = recv(client_socket, buffer, 1024, 0)) {

        printw("Received : %s\n", buffer);

        char *token = strtok(buffer, "/");
        char *messages[100];
        int i = 0;

        while(token != NULL) {
            messages[i] = token;
            token = strtok(NULL, "/");
            i++;
        }
        //Split the received string into a array

        //Clear the previous text
        wclear(windows[1]);
        redisplay_everything();        

        mvwprintw(windows[1], 1, 1, "Server response :");
        //Display the title

        for(int j = 0; j < i; j++) {
            mvwprintw(windows[1], j + 2, 2, "                        ");
            mvwprintw(windows[1], j + 2, 2, "%s", messages[j]);
            wrefresh(windows[1]);
        }
        //Display each messages into the right window
        
        memset(buffer, 0, 1024); //Clear the buffer
    }
}
