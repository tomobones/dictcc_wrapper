#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "user_interface.h"

// ________________________________________________________________
// public methods - implementations - vocabs

void init_ui(void) {
    initscr();
}

void display_vocabs(void) {

    attrset(A_BOLD);
    attrset(A_NORMAL);
    printw("- press any key -\n");

    refresh();
    getchar();
}

void cleanup_ui(void) {
    endwin();
}
