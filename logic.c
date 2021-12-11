#include "logic.h"
#include <ncurses.h>

#define POLE_1 length / 7 + 1
#define POLE_2 length / 2 - 2
#define POLE_3 3 * length / 4 + 1


void draw_poles(WINDOW* win, const int blocks[5]){
   int length, height; 
   int i, j;

   getmaxyx(win, height, length);

  for(i = 0; i < 5; i++){
      mvwaddch(win, height - 8 + i, POLE_1, ACS_BLOCK);         // center blocks

      for(j = 0; j < blocks[i]; j++){
          mvwaddch(win, height - 8 + i, POLE_1 - j, ACS_BLOCK);
          mvwaddch(win, height - 8 + i, POLE_1 + j, ACS_BLOCK);
      }
  }
}

void logic(int input){

}

