#include <string.h>
#include <ncurses.h>
#include <inttypes.h>

#include "popups.c"
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
* This function update the server_ip variable
*/
void update_server_ip(char *ip);

/*
* This function display the menu in the left window
*/
void display_menu();

/*
* This function update the cursor of the menu
*/
void update_cursor();

/*
* This function display the client id in the bottom of the left window
*/
void display_client_id();

/*
* Display current transaction in the right window
*/
void display_transaction();

/*
* This function redisplay everything, the menu, the cursor the client id, the server ip and
* the windows border. This function is meant to be used when a popup is closed
*/
void redisplay_everything();

/*
* Update the client id global var
*/
void update_client_id(int id);

#endif
