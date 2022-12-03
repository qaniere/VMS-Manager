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

int *ask_vm_range() {

    flushinp();
    //Clear the input buffer

   static int result[2] = {0, 0};

    WINDOW *popup = create_popup(LINES / 2, COLS /2, LINES /4, COLS /4, "Display VMS");
    //Create a popup window
    
    echo(); 
    //Enable keyboard input

    mvwprintw(popup, 2, 2, "Enter the range of VMS you want to display");
    mvwprintw(popup, 3, 2, "Example: 1-5");
    mvwprintw(popup, 4, 2, "VMS range: ");
    //Print the instructions

    wrefresh(popup);
    //Refresh the popup window

    char *range = malloc(10 * sizeof(char));
    //Create a string to store the range

    mvwgetstr(popup, 4, 13, range);
    wrefresh(popup);
    //Get the range from the user

    if(atoi(&range[0]) == 0 || atoi(&range[2]) == 0) {
        result[0] = 0;
        result[1] = 0;

    } else {
        result[0] = atoi(&range[0]);
        result[1] = atoi(&range[2]);
    }

    free(range);
    //Free the memory allocated for the range

    wclear(popup);
    wborder(popup, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(popup);
    delwin(popup);
    //Delete the popup window

    noecho();
    return result;
}
