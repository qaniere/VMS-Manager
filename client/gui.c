//SIF1015 - Fall 2022
//Made by Julio Bangadebia and Quentin Anière

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

char *menus_choices[] = {
    "1 - Add a VMS",
    "2 - List VMS",
    "3 - Delete a VMS",
    "4 - Execute binary code on VMS",
    "5 - Quit the program"
};
//Contains the choices of the main menu

int cursor_y = -1;
int current_choice = 0;
//Contains the current choice of the main menu and the cursor position

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

    cursor_y = 0 + 3;
    //Set the cursor position, 3 is the number of lines of the header
    
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

    noecho();
    //Disable echo of user input

    wrefresh(left_window);
    wrefresh(right_window);
    //Refresh windows

    display_menu();
    update_cursor();

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
    
        int c = getch(); //Get user input
        if(c == 'q' || c == 'Q') {
            break;

        } else if(c == KEY_UP) {
        //If the user press the up arrow

            if(cursor_y > 3) {
            //If the cursor is not at the top of the menu, move it up
                cursor_y--;
                current_choice--;
                update_cursor();   
            }
            

        } else if(c == KEY_DOWN) {
        //If the user press the down arrow

            if(cursor_y < 8) {
            //If the cursor is not at the bottom of the menu, move it down

                cursor_y++;
                current_choice++;
                update_cursor();
            }

        } else if(c == 10) {
        //Enter key

            if(current_choice == 0) {
            //Add a VMS
                addOperationToTransaction(transaction, "A");
                send_transaction(socket_fd, client_id, transaction->operations);
                transaction->operations[0] = '\0'; //Reset the string, so it can be reused
                transaction = createTransaction(client_id);


            } else if(current_choice == 1) {
            //List VMS
                int *range = ask_vm_range("Display VMS", "Enter the range of VMS to display");
                char *operation = malloc(10);
                //Create a string that will contain the operation

                if(range[0] != 0 && range[1] != 0) {
                    sprintf(operation, "L %d-%d", range[0], range[1]);
                    addOperationToTransaction(transaction, operation);
                    //Add the operation to the transaction 
                    send_transaction(socket_fd, client_id, transaction->operations);
                    transaction->operations[0] = '\0'; //Reset the string, so it can be reused
                    transaction = createTransaction(client_id);
                }

                free(operation);
                redisplay_everything();
                //Free the string allocated memory and redisplay everything
                //because the popup may have deleted some text

            } else if(current_choice == 2) {
                int vms_to_delete = ask_vm_number("Delete a VMS", "Enter the VMS number to delete");
                char *operation = malloc(10);

                if(vms_to_delete != 0) {
                    sprintf(operation, "E %d", vms_to_delete);
                    addOperationToTransaction(transaction, operation);
                    send_transaction(socket_fd, client_id, transaction->operations);
                    transaction->operations[0] = '\0'; //Reset the string, so it can be reused
                    transaction = createTransaction(client_id);
                }

                free(operation);
                redisplay_everything();

            } else if(current_choice == 3) {
                int vms_to_execute = ask_vm_number("Execute binary code", "Enter the VMS number to execute to");
                char *filename = ask_string("Enter filename", "Enter the filename :");

                char *operation = malloc(sizeof(char) * (strlen(filename) + 20));

                if(vms_to_execute != 0) {
                    sprintf(operation, "X %d %s", vms_to_execute, filename);
                    addOperationToTransaction(transaction, operation);
                    send_transaction(socket_fd, client_id, transaction->operations);
                    transaction->operations[0] = '\0'; //Reset the string, so it can be reused
                    transaction = createTransaction(client_id);
                }

                free(operation);
                free(filename);
                redisplay_everything();

            } else if(current_choice == 4) {
            //Quit the program
                break;
            }
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
* This function display the menu in the left window
*/
void display_menu() {
    for(int i = 0; i < 5; i++) {
        mvwprintw(windows[0], i + 3, 10, "                        ");
        //Clear the previous text

        mvwprintw(windows[0], i + 3, 10, "%s", menus_choices[i]);
        wrefresh(windows[0]);
    }
}

/*
* This function update the cursor of the menu
*/
void update_cursor() {
    mvwprintw(windows[0], cursor_y - 1, 8, " ");
    mvwprintw(windows[0], cursor_y + 1, 8, " ");
    //Clear the previous cursor

    mvwprintw(windows[0], cursor_y, 8, ">");
    wrefresh(windows[0]);
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
    display_menu();
    update_cursor();
    display_server_ip();
    display_client_id();

    box(windows[0], 0, 0);
    box(windows[1], 0, 0);

    mvwprintw(windows[0], 0, 2, "Transmission");
    mvwprintw(windows[1], 0, 2, "Reception");

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
