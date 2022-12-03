#include <ncurses.h>

#ifndef POPUPS_H
#define POPUPS_H

/*
* This function creates a popup window with specified coordinates and title
*/
WINDOW *create_popup(int start_y, int start_x, int end_y, int end_x, char *title);

#endif
