#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <stdbool.h>
#include <locale.h>
#include <string.h>

#include "user_interface.h"
#include "data_center.h"

#define BUFFER_MAX 256
//#define _XOPEN_SOURCE_EXTENDED 1

// ________________________________________________________________
// private variables

static WINDOW *win_mark;
static WINDOW *win_nr;
static WINDOW *win_left;
static WINDOW *win_right;
static WINDOW *win_lists;
static WINDOW *win_user;

static int stdscr_x;
static int stdscr_y;
static int curs_pos_y = 0;
static int curs_pos_list_y = 0;
static int top_number = 1;
static int vocab_number = 0;
static int voclst_number = 0;


// ________________________________________________________________
// private methods - declarations

void display_vocabs_top_number(int top_number);
void display_voclists_top_number(int top_number);


// ________________________________________________________________
// public methods - implementations - vocabs

void init_ui(void) {
    setlocale(LC_CTYPE, "de_DE.UTF-8");

    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    getmaxyx(stdscr, stdscr_y, stdscr_x);

    win_mark = subwin(stdscr, stdscr_y-2, 1, 1, 1);
    win_nr = subwin(stdscr, stdscr_y-2, 3, 1, 3);
    win_left = subwin(stdscr, stdscr_y-2, (stdscr_x - 5)/2-2, 1, 7);
    win_right = subwin(stdscr, stdscr_y-2, (stdscr_x - 5)/2-2, 1, (stdscr_x - 5)/2+1);
    win_lists = subwin(stdscr, 20, 60, (stdscr_y-20)/2, (stdscr_x-60)/2);
    win_user = subwin(stdscr, 20, 60, (stdscr_y-20)/2, (stdscr_x-60)/2);
}

bool loop_vocabs_ui(void) {
    char input;
    bool must_exit = false;
    display_vocabs_top_number(1);
    vocab_data_t *vocab = NULL;
    bool retval = false;

    while (!must_exit) {
        input = getchar();
        switch (input) {
            case 'q':
                must_exit = true;
                retval = false;
                break;
            case 'a':
                must_exit = true;
                retval = true;
                break;
            case 'k':
                if (curs_pos_y > 0) curs_pos_y--;
                display_vocabs_top_number(1);
                break;
            case 'j':
                if (curs_pos_y < vocab_number - 1) curs_pos_y++;
                display_vocabs_top_number(1);
                break;
            case ' ':
                vocab = vocab_for_nr(curs_pos_y + 1);
                vocab->is_marked = !(vocab->is_marked);
                display_vocabs_top_number(1);
                break;
            default:
                break;
        }
    }
    return retval;
}

void get_user_passwd(char* user, char *pass) {
    wclear(win_user);
    wborder(win_user, 0,0,0,0,0,0,0,0);
    mvwprintw(win_user, 2, 2, "enter your username: ");
    wrefresh(win_user);
    wgetnstr(win_user, user, BUFFER_MAX);
    mvwprintw(win_user, 3, 2, "enter your password: ");
    refresh();
    wrefresh(win_user);
    wgetnstr(win_user, pass, BUFFER_MAX);
}

void get_voclst(char *list_id_str) {
    char input;
    bool must_exit = false;
    display_voclists_top_number(1); 
    voclst_data_t *voclst = NULL;

    while (!must_exit) {
        input = getchar();
        switch (input) {
            case 'q':
                must_exit = true;
                strcpy(list_id_str, "");
                break;
            case 'j':
                if (curs_pos_list_y < voclst_number - 1) curs_pos_list_y++;
                display_voclists_top_number(1);
                break;
            case 'k':
                if (curs_pos_list_y > 0) curs_pos_list_y--;
                display_voclists_top_number(1);
                break;
            case ' ':
                voclst = voclst_for_nr(curs_pos_list_y + 1);
                sprintf(list_id_str, "%d", voclst->id);
                must_exit = true;
                break;
            default:
                break;
                
        }
    }
}

void cleanup_ui(void) {
    endwin();
}


// ________________________________________________________________
// public methods - implementations - vocabs

void display_vocabs_top_number(int top_nr) {
    top_number = top_nr;
    
    int counter = 0;

    //wclear(win_mark);
    //wclear(win_nr);
    //wclear(win_left);
    //wclear(win_right);

    vocab_data_t *vocab = vocab_for_nr(counter + top_number);

    while (vocab != NULL) {
    
        wattrset(win_mark, A_BOLD);
        if (curs_pos_y == counter) {
            wattrset(win_nr, A_BOLD);
            wattrset(win_left, A_BOLD);
            wattrset(win_right, A_BOLD);
        } else {
            wattrset(win_nr, A_NORMAL);
            wattrset(win_left, A_NORMAL);
            wattrset(win_right, A_NORMAL);
        }
        
        mvwprintw(win_mark, counter, 0, "%c\n", vocab->is_marked ? 'X' : ' ');
        mvwprintw(win_nr, counter, 0, "%d\n", vocab->nr);
        mvwprintw(win_left, counter, 0, "%s\n", vocab->vl);
        mvwprintw(win_right, counter, 0, "%s\n", vocab->vr);

        vocab = vocab_for_nr(++counter + top_number);
    }
    
    vocab_number = counter;

    wrefresh(win_left);
    wrefresh(win_right);
    wrefresh(win_nr);
    wrefresh(win_mark);

    attrset(A_NORMAL);
    mvprintw(stdscr_y-1, 1, "Press 'q' to exit...");
    refresh();
}

void display_voclists_top_number(int top_number) {
    int counter = 0;
    voclst_data_t *voclst = voclst_for_nr(counter + top_number);
    wclear(win_lists);
    while (voclst != NULL) {
        if (curs_pos_list_y == counter) wattrset(win_lists, A_BOLD);
        else wattrset(win_lists, A_NORMAL);
        mvwprintw(win_lists, counter+2, 2, "%d: %s\n", voclst->nr, voclst->name);
        voclst = voclst_for_nr(++counter + top_number);
    }
    voclst_number = counter;
    wborder(win_lists, 0,0,0,0,0,0,0,0);
    wrefresh(win_lists);
}
