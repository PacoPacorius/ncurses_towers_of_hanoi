/* This works! Initialisation is complete. Next is to make the main game loop, make a menu with three choices and then draw over those choices
 *
 * The window does show I'm just a silly goose
 *
 * Make a menu  -done!
 *
 * Make the menu horizontal
 *
 * Main game loop prototype! Will only be able to scroll through the menu's options
 *
 * Second window and drawing the towers
 */

#include <ncurses.h>
#include <menu.h>

#include "menu.h"

void init_ncurses();
WINDOW* create_win(int menu_height, int menu_width, int start_y, int start_x);


int main(){
    /* Variables that need all of the scope */
    WINDOW* towers;
    ITEM** my_items;
    MENU* menu;

    init_ncurses();

        // dimensions for the selection window //
        int towers_height = 6;
        int towers_length = 40;
        int start_x = (COLS - towers_length) / 2;
        int start_y = (LINES - towers_height) / 2 + (LINES / 7);
        // dimensions for the selection window //
 
    /* Variables that need all of the scope */

    towers = create_win(towers_height, towers_length, start_y, start_x);             // allocate memory for the selection window
    my_items = create_items(towers, towers_height, towers_length, start_y, start_x); // subroutine that allocates memory for the selection menu items (see menu.c)
    menu = new_menu(my_items);                                                       // associate the items with their menu

    set_menu_win(menu, towers);                                                      // Associate the menu with the selection window
    set_menu_sub(menu, derwin(towers, 4, 38, 1, 1));                                 // Create its own little window within towers so that towers still looks pretty
    //mvprintw(LINES - 2, COLS - 7, "Hello!");

    /* take care of all the visual stuff */
    refresh();                          
    post_menu(menu);
    wrefresh(towers);
    /* take care of all the visual stuff */

    /* temp game loop, will be removed once the subroutine for the permanent game loop is implemented */
    while(getch() != 'q'){
        //refresh();
    }
    /* temp game loop, will be removed once the subroutine for the permanent game loop is implemented */

    /* memory deallocation */
    unpost_menu(menu);
    free_menu(menu);
    free_item(my_items[1]);
    free_item(my_items[2]);
    free_item(my_items[3]);
    delwin(towers);
    /* memory deallocation */

    /* end of program */
    endwin();
    return 0;
    /* end of program */
}


void init_ncurses(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, true);
    curs_set(0);

}

WINDOW* create_win(int menu_height, int menu_width, int start_y, int start_x){
    WINDOW* menu;

    menu = newwin(menu_height, menu_width, start_y, start_x);
    box(menu, 0, 0);
    //mvwaddstr(menu, 1, 1, "Testing Testing one two one two");

    return menu;
}
