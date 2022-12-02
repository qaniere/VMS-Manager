#include "popups.h"

WINDOW *create_popup(int start_y, int start_x, int end_y, int end_x, char *title) {
    WINDOW *popup = newwin(start_y, start_x, end_y, end_x);
    box(popup, 0, 0);
    mvwprintw(popup, 0, 2, title);
    return popup;
}

int select_vms_number() {

    int lines = LINES;
    int columns = COLS;

    WINDOW *popup = create_popup(lines / 2, columns / 2, lines / 4, columns / 4, "Select a VMS number");
    wrefresh(popup);

    char user_input[10];

    mvwprintw(popup, 2, 2, "Type the number of VMS you want to use :");
    mvwprintw(popup, 4, 4, " > ");
    // mvgetnstr(2, 4, user_input, 10);
    wrefresh(popup);
    //Get the user input

    int vms_number = atoi(user_input);
    //Convert the user input to an int

    delwin(popup);
    //Delete the popup window

    return vms_number;
}   

