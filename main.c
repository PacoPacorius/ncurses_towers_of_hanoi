/* The window does show I'm just a silly goose
 *
 * Make a menu  -done!
 *
 * Make the menu horizontal -done
 *
 * Main game loop prototype! Will only be able to scroll through the menu's options -done
 *
 * Second window and drawing the win (also giving the selection menu options more space)
 * 1. Make an array to manage the blocks  -done
 * 2. Implement three stacks -done
 * 3. Draw a window -done
 * 4. Draw a horizontal line with numbers (the poles are invisible over the numbers) -done
 * 5. Draw the blocks in series on pole 1
 */

#include <ncurses.h>
#include <menu.h>

#include "menu.h"
#include "logic.h"
#include "stack.h"

#define BLOCK_NUMBER 5

void init_ncurses();
WINDOW* create_win_with_menu(MENU* menu);
WINDOW* create_win();


int main(){
    /* Variables that need all of the scope */
    WINDOW* win;
    WINDOW* tower_win;
    ITEM** my_items;
    MENU* menu;

    int c;                                          // for handling user unput
    int move = 0;                                   // 1 when user is about to move a block
    const int blocks[BLOCK_NUMBER] = { 1, 2, 3, 4, 5 };   // the numbers will hopefully help with drawing the blocks
    struct Stack* towers[3];                        // the blocks will go in here
    /* Variables that need all of the scope */

    /* various initialisation subroutines */
    init_ncurses();

    int i = 0;
    for(i = 0; i < 3; i++)
        towers[i] = create_stack(BLOCK_NUMBER);     // allocate memory for the three tower stacks

    for(i = 4; i > -1; i--)
        push(towers[0], blocks[i]);                 // put all of the blocks in series in the first tower stack

    my_items = create_items(win);                   // subroutine that allocates memory for the selection menu items (see menu.c)
    menu = new_menu(my_items);                      // associate the items with their menu
    win = create_win_with_menu(menu);               // allocate memory for the selection window

    tower_win = create_win();
    /* various initialisation subroutines */

    /* take care of all the visual stuff */
    refresh();                          
    post_menu(menu);
    wrefresh(win);
    wrefresh(tower_win);
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
        logic(c, &move);    // will eventually handle the logic of the game
        wrefresh(win);
    }
    /* temp game loop, will be removed once the subroutine for the permanent game loop is implemented */

    /* memory deallocation */
    unpost_menu(menu);
    free_menu(menu);
    for(i = 1; i < 4; i++){
        free_item(my_items[i]);
    }
    delwin(win);
    for(i = 0; i < 2; i++){
        free(towers[i]->array); // deallocate the int array of the stack
        free(towers[i]);        // deallocate the stack object
    }
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

WINDOW* create_win_with_menu(MENU* menu){
    int towers_height = 4;
    int towers_length = 40;
    int start_x = (COLS - towers_length) / 2;
    int start_y = (LINES - towers_height) / 2 + (LINES / 4);
    WINDOW* towers;

    towers = newwin(towers_height, towers_length, start_y, start_x);
    //box(towers, 0, 0);

    set_menu_win(menu, towers);                                                      // Associate the menu with the selection window
    set_menu_sub(menu, derwin(towers, towers_height - 2, towers_length - 2, 1, 1));  // Create its own little window within towers so that towers still looks pretty
    menu_opts_off(menu, O_SHOWDESC);
    set_menu_format(menu, 1, 3);
    set_menu_mark(menu, "");

    return towers;
}

WINDOW* create_win(){
    int i;

    int towers_height = 8;
    int towers_length = 40;
    int start_x = (COLS - towers_length) / 2;
    int start_y = (LINES - towers_height) / 2 - (LINES / 8);
    WINDOW* towers;

    towers = newwin(towers_height, towers_length, start_y, start_x);
    box(towers, 0, 0);

    wmove(towers, towers_height - 3, 1);
    for(i = 1; i < towers_length - 1; i++)
       waddch(towers, ACS_HLINE);

    mvwprintw(towers, towers_height - 2, towers_length / 7, "[1]");
    mvwprintw(towers, towers_height - 2, towers_length / 2 - 3, "[2]");
    mvwprintw(towers, towers_height - 2, 3 * towers_length / 4, "[3]");
    return towers;
}
