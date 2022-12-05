//SIF1015 - Fall 2022
//Made by Julio Bangadebia and Quentin Anière

#include "popups.h"

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
WINDOW *create_popup(int start_y, int start_x, int end_y, int end_x, char *title) {
    WINDOW *popup = newwin(start_y, start_x, end_y, end_x);
    box(popup, 0, 0);
    //Create a window with a border

    mvwprintw(popup, 0, 2, title);
    //Print the title of the popup onto the border

    return popup;
}

/*
* Ask the user to enter an range of VMS numbers like "x-y" and return the range.
* If the user enters a wrong range, the function will return 0-0
* This function create a popup window to do so
*/
int *ask_vm_range(char *title, char *message) {

    flushinp();
    //Clear the input buffer

   static int result[2] = {0, 0};

    WINDOW *popup = create_popup(LINES / 2, COLS /2, LINES /4, COLS /4, title);
    //Create a popup window (centered)
    
    echo(); 
    //Enable keyboard input

    mvwprintw(popup, 2, 2, message);
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

/*
* Ask the user to enter a VMS number and return it.
* If the user enters a wrong number, the function will return 0
* This function create a popup window to do so
* @param title The title of the popup
* @param message The message to display to the user
* @return The VMS number entered by the user
*/
int ask_vm_number(char *title, char *message) {

    flushinp();
    //Clear the input buffer

    WINDOW *popup = create_popup(LINES / 2, COLS /2, LINES /4, COLS /4, title);
    //Create a popup window (centered)
    
    echo(); 
    //Enable keyboard input

    mvwprintw(popup, 2, 2, message);
    mvwprintw(popup, 3, 2, "VMS number: ");
    //Print the instructions

    wrefresh(popup);
    //Refresh the popup window

    char *number = malloc(10 * sizeof(char));
    //Create a string to store the range

    mvwgetstr(popup, 3, 14, number);
    wrefresh(popup);
    //Get the range from the user

    int result = atoi(number);

    free(number);
    //Free the memory allocated for the range

    wclear(popup);
    wborder(popup, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(popup);
    delwin(popup);
    //Delete the popup window

    noecho();
    return result;
}

/*
* Ask the user to enter a string and return it.
* This function create a popup window to do so
* @param title The title of the popup
* @param message The message to display to the user
* @return The string entered by the user
*/
char *ask_string(char *title, char *message) {

    flushinp();
    //Clear the input buffer

    WINDOW *popup = create_popup(LINES / 2, COLS /2, LINES /4, COLS /4, title);
    //Create a popup window (centered)
    
    echo(); 
    //Enable keyboard input

    mvwprintw(popup, 2, 2, message);
    mvwprintw(popup, 3, 2, "String: ");
    //Print the instructions

    wrefresh(popup);
    //Refresh the popup window

    char *string = malloc(100 * sizeof(char));
    //Create a string to store the range

    mvwgetstr(popup, 3, 10, string);
    wrefresh(popup);
    //Get the range from the user

    wclear(popup);
    wborder(popup, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(popup);
    delwin(popup);
    //Delete the popup window

    noecho();
    return string;
}
