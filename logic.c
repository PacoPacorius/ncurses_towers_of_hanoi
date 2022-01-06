#include "logic.h"
#include <ncurses.h>

#define POLE_1 length / 7 + 1
#define POLE_2 length / 2 - 2
#define POLE_3 3 * length / 4 + 1

int win_clause(struct Stack* target){
    int check_succesful = 1, i;
    char str[2];
    for(i = 0; i < 5; i++){
        if(5 - i != target->array[i]) check_succesful = 0;
    snprintf(str, 2, "%d", 5 - i);
    //mvwaddstr(stdscr, LINES - 7, 2, str);
    }
        
    
    return check_succesful;
}

void print_stack_contents(struct Stack* stack_array[3], WINDOW* win);

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

int  move_illegal(struct Stack* destination, struct Stack* source){
    char temp[5];

    snprintf(temp, 5, "%d", source->array[source->top]);
    //mvwaddstr(stdscr, LINES - 2, COLS / 2 - 2, temp);

    snprintf(temp, 5, "%d", destination->array[destination->top]);
    //mvwaddstr(stdscr, LINES - 2, COLS / 2 + 2, temp);

    if(source->array[source->top] == -1) return 1;
    if(source->array[source->top] <= destination->array[destination->top] || destination->array[destination->top] < 1) return 0;
    return 1;
}

void move_block(struct Stack* destination, struct Stack* source){
    int temp;

    if(source->array[source->top] != -1 && move_illegal(destination, source) != 1) {
        temp = pop(source);
        if(temp != -1)
            push(destination, temp); //this error checking still doesnt work :((
   }
}

void update_blocks(struct Stack* stack_array[3], WINDOW* win){
    int i, j, k, l, block_num;
    int length, height;
    int x_offset;
    char str[5];

    getmaxyx(win, height, length);

    for(i = 0; i < 3; i++){                 // iterates through the 3 poles
        switch(i){
            case 0:
                x_offset = POLE_1;
                break;
            case 1:
                x_offset = POLE_2;
                break;
            case 2:
                x_offset = POLE_3;
                break;
        }


        block_num = number_of_items(stack_array[i]);        // number of items in a stack 
        //mvwprintw(stdscr, LINES - 2, x_offset, "%i", block_num);    // debugging this will go away soon

        //print_stack_contents(stack_array, win);
        

        for(j = 0; j < 5; j++){    // iterates through the stack in LIFO order

            k = stack_array[i]->array[j];           // contains the number(block id) of the stack item we are currently looking at
            snprintf(str, 5, "%d", k);

            if(k >= 0){                                                    // if this isn't a blank space
                mvwaddch(win, height - 4 - j, x_offset, ACS_BLOCK); // draw the centre block 

                for(l = 0; l < k; l++){                                                     // Give the boxes width
                    mvwaddch(win, height - 4 - j, x_offset - l, ACS_BLOCK);
                    mvwaddch(win, height - 4 - j, x_offset + l, ACS_BLOCK);
                }  
            }
            else{
                for(l = 0; l < 5; l++){
                    mvwaddch(win, height - 4 - j, x_offset - l, ' ');      // erase the centre block if there is a -1 in this place in the stack
                    mvwaddch(win, height - 4 - j, x_offset + l, ' ');      // erase the centre block if there is a -1 in this place in the stack
                }

            }
           
               
        }
    }
}

void print_stack_contents(struct Stack* stack_array[3], WINDOW* win){
    char temp[5];
    int i, j, x_offset;
    int length, height;

    getmaxyx(win, height, length);

    for(i = 0; i < 3; i++){
        switch(i){
            case 0:
                x_offset = POLE_3;
                break;
            case 1:
                x_offset = POLE_2;
                break;
            case 2:
                x_offset = POLE_1;
                break;
        }
        for(j = 0; j < 5; j++){

            snprintf(temp, 5, "%d", stack_array[i]->array[j]);
            mvwaddch(stdscr, LINES - 7 + j, COLS - x_offset + 1, ' ');
            mvwaddstr(stdscr, LINES - 7 + j, COLS - x_offset, temp);
        }
    }

}
