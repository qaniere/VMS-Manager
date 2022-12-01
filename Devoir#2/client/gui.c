#include "gui.h"

int lines, columns;

char server_ip[16] = " ";
WINDOW *windows[2] = {NULL, NULL};

char *menus_choices[4] = {
    "Add a VMS",
    "List VMS",
    "Delete a VMS",
    "Execute binary code on VMS"
};

int cursor_y = 0;
int current_choice = 0;

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

    cursor_y = 0 + 4;
    
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

    noecho();
    //Disable echo of user input

    wrefresh(left_window);
    wrefresh(right_window);
    //Refresh windows

    display_menu();
    update_cursor();

    display_server_ip();
    refresh();
}

/*
* This function is a loop that make the GUI update and wait for user input
*/
void gui_loop() {
    while(1) {

        for(int i = 0; i < 2; i++) {
            if(windows[i] == NULL) {
                wrefresh(windows[i]);
            }
        }

        int c = getch();
        if(c == 'q') {
            break;

        } else if(c == KEY_UP) {
            if(cursor_y > 0 + 4) {
                cursor_y--;
                current_choice--;
                update_cursor();
                
            }

        } else if(c == KEY_DOWN) {

            if(cursor_y < 0 + 4 + 3) {
                cursor_y++;
                current_choice++;
                update_cursor();
            }

        } else if(c == 10) {
            mvwprintw(windows[1], 2, 2, "                                         ");
            mvwprintw(windows[1], 2, 2, "Action: %s", menus_choices[current_choice]);
            wrefresh(windows[1]);
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
* This function prints a message in the window
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
* This function update the server_ip variable
*/
void update_server_ip(uint32_t ip) {
    sprintf(server_ip, "%d.%d.%d.%d", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
    display_server_ip();
} 

/*
* This function display the menu in the left window
*/
void display_menu() {
    for(int i = 0; i < 4; i++) {
        mvwprintw(windows[0], i + 4, 10, "                        ");
        //Clear the previous text

        mvwprintw(windows[0], i + 4, 10, "%s", menus_choices[i]);
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
