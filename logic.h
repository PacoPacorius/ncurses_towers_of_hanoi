#ifndef _LOGIC
#define _LOGIC

#include <ncurses.h>
#include <stdlib.h>
#include <menu.h>

#include "stack.h"

int win_clause(struct Stack* target);

void draw_poles(WINDOW* win, const int blocks[5]);

void move_block(struct Stack* destinatio, struct Stack* source);

void update_blocks(struct Stack* stack_array[3], WINDOW* win);

#endif
