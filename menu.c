#include "menu.h"

ITEM** create_items(){
    ITEM** selection;
    int i;

    char* choices[] = {
        "  Pole 1  ",
        "  Pole 2  ",
        "  Pole 3  "
    };

    selection = (ITEM **)calloc(number_choices + 1, sizeof(ITEM*));

    for(i = 0; i < number_choices; ++i)
        selection[i] = new_item(choices[i], choices[i]);
    selection[number_choices] = (ITEM *)NULL;

    return selection;
}

