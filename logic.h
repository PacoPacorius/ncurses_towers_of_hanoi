#ifndef _LOGIC
#define _LOGIC

#include <ncurses.h>
#include <stdlib.h>
#include <menu.h>

#include "stack.h"

void logic(int input);

void draw_poles(WINDOW* win, const int blocks[5]);

#endif
