#include "popups.h"

/*
* This function creates a popup window with specified coordinates and title
*/
WINDOW *create_popup(int start_y, int start_x, int end_y, int end_x, char *title) {
    WINDOW *popup = newwin(start_y, start_x, end_y, end_x);
    box(popup, 0, 0);
    //Create a window with a border

    mvwprintw(popup, 0, 2, title);
    //Print the title of the popup onto the border

    return popup;
}


