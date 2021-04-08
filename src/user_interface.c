#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>

#include "user_interface.h"
#include "data_center.h"

// ________________________________________________________________
// public methods - implementations - vocabs

void init_ui(void) {
    initscr();
}

void display_vocabs(void) {

    int vocab_number = 1;
    vocab_data_t *vocab = vocab_for_nr(vocab_number);
    while (vocab != NULL) {
        attrset((vocab->is_marked) ? A_BOLD : A_NORMAL);
        printw("%d: ", vocab->nr);
        attrset(A_NORMAL);
        printw("%s ", vocab->vl);
        attrset(A_BOLD);
        printw(":");
        attrset(A_NORMAL);
        printw(" %s\n", vocab->vr);
        vocab = vocab_for_nr(++vocab_number);
    }

    refresh();
    getchar();
}

void cleanup_ui(void) {
    endwin();
}
