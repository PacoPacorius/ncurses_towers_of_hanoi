#include "menu.h"

char* choices[] = {
    "[1]",
    "[2]",
    "[3]"
};

ITEM** create_items(WINDOW* win, int height, int width, int start_y, int start_x){
    ITEM** selection;
    int i;

    char* choices[] = {
        "[1]",
        "[2]",
        "[3]"
    };

    selection = (ITEM **)calloc(number_choices + 1, sizeof(ITEM*));

    for(i = 0; i < number_choices; ++i)
        selection[i] = new_item(choices[i], choices[i]);
    selection[number_choices] = (ITEM *)NULL;

    return selection;
}

