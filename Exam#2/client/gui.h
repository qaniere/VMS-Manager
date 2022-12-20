//SIF1015 - Fall 2022
//Made by Quentin Anière

#include <string.h>
#include <ncurses.h>
#include <inttypes.h>

#include "transaction.c"

#ifndef GUI_H
#define GUI_H

/*
* This function initializes the ncurses library and creates a window
*/
void init_gui();

/*
* This function is a loop that make the GUI update and wait for user input
*/
void gui_loop();

/*
* This function destroys the window and ends the ncurses library
*/
void gui_cleanup();

/*
* This function display the server ip in the bottom of the left window
*/
void display_server_ip();

/*
* This function update the server_ip global variable
* @param ip The new server ip
*/
void update_server_ip(char *ip);


/*
* This function display the client id in the bottom of the left window
*/
void display_client_id();


/*
* This function redisplay everything, the menu, the cursor the client id, the server ip and
* the windows border. This function is meant to be used when a popup is closed
*/
void redisplay_everything();

/*
* Update the client id global var
* @param id The new client id
*/
void update_client_id(int id);


/*
* Update the socket fd global var
* @param fd The new socket fd
*/
void update_socket_fd(int fd);

/*
* This function is actually defined in the client_socket.c file
*/
void send_transaction(int socket_fd, int client_id, char *operations);

/*
* This function listen for the server and display any received message in the right window
* @param socket The socket to listen on
*/
void *server_listenner(void *socket);

#endif
