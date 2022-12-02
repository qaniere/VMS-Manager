#include <string.h>
#include <ncurses.h>

#include "popups.c"

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
void update_server_ip(uint32_t ip);

/*
* This function display the menu in the left window
*/
void display_menu();

/*
* This function update the cursor of the menu
*/
void update_cursor();

/*
* This function display the current VMS number in the left window
*/
void display_current_vms();

#endif
