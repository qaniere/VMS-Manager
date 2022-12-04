#include <ncurses.h>

#ifndef POPUPS_H
#define POPUPS_H

/*
* This function creates a popup window with specified coordinates and title
* It returns the window pointer
* @param int start_y : the y coordinate of the top left corner of the window
* @param int start_x : the x coordinate of the top left corner of the window
* @param int end_y : the y coordinate of the bottom right corner of the window
* @param int end_x : the x coordinate of the bottom right corner of the window
* @param char *title : the title of the window
* @return WINDOW * : the window pointer
*/
WINDOW *create_popup(int start_y, int start_x, int end_y, int end_x, char *title);

/*
* Ask the user to enter an range of VMS numbers like "x-y" and return the range.
* If the user enters a wrong range, the function will return 0-0
* This function create a popup window to do so
*/
int *ask_vm_range(char *title, char *message);

/*
* Ask the user to enter a VMS number and return it.
* If the user enters a wrong number, the function will return 0
* This function create a popup window to do so
* @param title The title of the popup
* @param message The message to display to the user
* @return The VMS number entered by the user
*/
int ask_vm_number(char *title, char *message);

/*
* Ask the user to enter a string and return it.
* This function create a popup window to do so
* @param title The title of the popup
* @param message The message to display to the user
* @return The string entered by the user
*/
char *ask_string(char *title, char *message);

#endif
