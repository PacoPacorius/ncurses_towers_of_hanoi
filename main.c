/* Fun little project, towers of hanoi on the terminal through ncurses because why not. I finally finished something I can show and wrapped my head around the ncurses lib. Have fun
 * uncommenting all the debugging stuff at logic.c woo numbers hell yeah
 *
 *
 * It could use some more work, like a variable block number (probs a lot of work I'm too lazy for that), triggering the win clause before getch() and some cosmetic stuff but 
 * who's got the time for that
 */

#include <ncurses.h>
#include <menu.h>

#include "menu.h"
#include "logic.h"
#include "stack.h"

#define BLOCK_NUMBER 5
#define POLE_1 towers_length / 7
#define POLE_2 towers_length / 2 - 3
#define POLE_3 3 * towers_length / 4

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
    int selection = 0;
    struct Stack* temp_stack = NULL;
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
    update_blocks(towers, tower_win);                                                    // redraw the blocks to their correct positions
    wrefresh(tower_win);
    /* take care of all the visual stuff */

    /* temp game loop, will be removed once the subroutine for the permanent game loop is implemented */ // there is absolutely no reason why this shouldn't be the main game loop
    while((c = getch()) != 'q'){
        if(win_clause(towers[2]) == 1) break; // for some reason if I put this on the loop check next to getch() it does not work, so manual break it is
        switch(c){
            case KEY_RIGHT:
                menu_driver(menu, REQ_RIGHT_ITEM);
                break;
            case KEY_LEFT:
                menu_driver(menu, REQ_LEFT_ITEM);
                break;
            case 's': // I wanted to use enter but it didn't work so s(elect) it is
                if(selection == 1){                                                     // if player has selected a source
                    selection = 0;                                                      

                    move_block(towers[item_index(current_item(menu))], temp_stack);     // move a block from the source to the destination
                    mvprintw(LINES - 1, 1, "              ");                           // erase "Move to where?"

                    update_blocks(towers, tower_win);                                   // redraw the blocks to their new positions
                    wrefresh(tower_win);
                }
                else{
                    selection = 1;

                    temp_stack = towers[item_index(current_item(menu))];                // get ready to move a block (thank god I used pointers this might have been quite a pain otherwise)

                    mvprintw(LINES - 1, 1, "Move to where?");                           // player feedback
                }
                break;
        }
        wrefresh(win);
    }
    /* temp game loop, will be removed once the subroutine for the permanent game loop is implemented */ // yeah right dream on
    int towers_length, tower_height;
    getmaxyx(tower_win, tower_height, towers_length);                                   // this is used to align the victory message

    if(win_clause(towers[2]) == 1){
        mvwaddstr(stdscr, 3, (COLS - towers_length) / 2 + POLE_1, "Congrats! You're winner!");  // aww yeahhhh
        getch();
    }
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
    printf("Thanks for playing! <3\n");
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

WINDOW* create_win_with_menu(MENU* menu){       // this creates the lower menu
    int towers_height = 4;
    int towers_length = 40;
    int start_x = (COLS - towers_length) / 2;
    int start_y = (LINES - towers_height) / 2 + (LINES / 4);
    WINDOW* towers;

    towers = newwin(towers_height, towers_length, start_y, start_x);
    box(towers, 0, 0);

    set_menu_win(menu, towers);                                                      // Associate the menu with the selection window (I am referring to the lower window here)
    set_menu_sub(menu, derwin(towers, towers_height - 2, towers_length - 2, 1, 1));  // This is necessary to create a border around the selecction menu, without this the border overwrites the menu
    menu_opts_off(menu, O_SHOWDESC);                                                 
    set_menu_format(menu, 1, 3);                                                     // make the menu horizontal
    set_menu_mark(menu, "");                                                         // no need for a symbol I don't think

    return towers;
}

WINDOW* create_win(){       // this creates the menu with all the blocks and such
    int i;

    int towers_height = 9;
    int towers_length = 40;
    int start_x = (COLS - towers_length) / 2;
    int start_y = (LINES - towers_height) / 2 - (LINES / 8);
    WINDOW* towers;

    towers = newwin(towers_height, towers_length, start_y, start_x);
    box(towers, 0, 0);

    wmove(towers, towers_height - 3, 1);                                            // these three lines draws that little line on the border
    for(i = 1; i < towers_length - 1; i++)
       waddch(towers, ACS_HLINE);

    mvwprintw(towers, towers_height - 2, POLE_1, "[1]");
    mvwprintw(towers, towers_height - 2, POLE_2, "[2]");
    mvwprintw(towers, towers_height - 2, POLE_3, "[3]");
    return towers;
}
