#if !defined menu_H_
#define menu_H_

#include <ncurses.h>
#include <stdlib.h>
#include <menu.h>

#define number_choices 3

ITEM** create_items(WINDOW* win, int height, int width, int start_y, int start_x);

#endif
