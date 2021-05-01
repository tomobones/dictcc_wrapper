#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <locale.h>

#include "user_interface.h"
#include "data_center.h"

#define _XOPEN_SOURCE_EXTENDED 1

// ________________________________________________________________
// public methods - implementations - vocabs

void init_ui(void) {
    setlocale(LC_CTYPE, "de_DE.UTF-8");
    initscr();
}

void display_vocabs(void) {

    int vocab_number = 1;
    vocab_data_t *vocab = vocab_for_nr(vocab_number);
    while (vocab != NULL) {
        //attrset((vocab->is_marked) ? A_BOLD : A_NORMAL);
        attrset(A_BOLD);
        printw("%d: ", vocab->nr);
        attrset(A_NORMAL);
        printw("%s ", vocab->vl);
        attrset(A_BOLD);
        printw(":");
        attrset(A_NORMAL);
        printw(" %s\n", vocab->vr);
        vocab = vocab_for_nr(++vocab_number);
    }

    attrset(A_NORMAL);
    printw("\nPress any key...");
    
    refresh();
    getchar();
}

void cleanup_ui(void) {
    endwin();
}
