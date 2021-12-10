/* The window does show I'm just a silly goose
 *
 * Make a menu  -done!
 *
 * Make the menu horizontal -done
 *
 * Main game loop prototype! Will only be able to scroll through the menu's options -done
 *
 * Second window and drawing the towers (also giving the selection menu options more space)
 * 1. Make an array to manage the blocks  -done
 * 2. Implement three stacks 
 * 3. Draw a window
 * 4. Draw a line with numbers (the poles are invisible over the numbers)
 * 5. Draw the blocks in series on pole 1
 */

#include <ncurses.h>
#include <menu.h>

#include "menu.h"
#include "logic.h"

void init_ncurses();
WINDOW* create_win(MENU * menu);


int main(){
    /* Variables that need all of the scope */
    WINDOW* towers;
    ITEM** my_items;
    MENU* menu;

    int c;
    bool move;
    int blocks[5] = { 1, 2, 3, 4, 5 };

    init_ncurses();
    /* Variables that need all of the scope */

    my_items = create_items(towers);        // subroutine that allocates memory for the selection menu items (see menu.c)
    menu = new_menu(my_items);              // associate the items with their menu
    towers = create_win(menu);                  // allocate memory for the selection window

    /* take care of all the visual stuff */
    refresh();                          
    post_menu(menu);
    wrefresh(towers);
    /* take care of all the visual stuff */

    /* temp game loop, will be removed once the subroutine for the permanent game loop is implemented */
    while((c = getch()) != 'q'){
        switch(c){
            case KEY_RIGHT:
                menu_driver(menu, REQ_RIGHT_ITEM);
                break;
            case KEY_LEFT:
                menu_driver(menu, REQ_LEFT_ITEM);
                break;
        }
        logic(c, &move);
        wrefresh(towers);
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

WINDOW* create_win(MENU* menu){
    int towers_height = 6;
    int towers_length = 40;
    int start_x = (COLS - towers_length) / 2;
    int start_y = (LINES - towers_height) / 2 + (LINES / 7);
    WINDOW* towers;

    towers = newwin(towers_height, towers_length, start_y, start_x);
    box(towers, 0, 0);

    set_menu_win(menu, towers);                                                      // Associate the menu with the selection window
    set_menu_sub(menu, derwin(towers, towers_height - 2, towers_length - 2, 1, 1));  // Create its own little window within towers so that towers still looks pretty
    menu_opts_off(menu, O_SHOWDESC);
    set_menu_format(menu, 1, 3);

    return towers;
}
