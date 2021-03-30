#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <regex.h>
#include <string.h>

#include "data_center.h"
#include "parser.h"
#include "exit_err.h"

typedef struct SubstrPos {
    long start;
    long end;
} substrpos_t;

// private methods - declaration

void set_initial_positions(substrpos_t *pos_id, substrpos_t *pos_lv, substrpos_t *pos_rv, char *html);
void pos_of_match_in_html(substrpos_t *pos, regex_t *rx, char *html_data);
void add_next_vocab(vocab_data_t *vocab_to_add, substrpos_t *pos_id, substrpos_t *pos_lv, substrpos_t *pos_rv, char *html);

// to be replaced...
void regex_match2string(regex_t rx, char** ptstrg, char* webdata);
void extract_data_from_strings(char *ids, char *lvocabs, char *rvocabs);

// helper
void print_str_from_to(char *string, int from, int to);


// public methods - implementation

bool parse_vocabs_from_html(char* html) {


    // set initial positions
    substrpos_t pos_id, pos_lv, pos_rv;
    set_initial_positions(&pos_id, &pos_lv, &pos_rv, html); 

    // recurive retrieve of data
    vocab_data_t vocab_to_add;
    add_next_vocab(&vocab_to_add, &pos_id, &pos_lv, &pos_rv, html);
    //vocab_add();

    
    return true;
}

// private methods - implementation

void set_initial_positions(substrpos_t *pos_id, substrpos_t *pos_lv, substrpos_t *pos_rv, char *html) {

    // compile regex
    regex_t rx;
    char *pat_ids = "var idArr = new Array([^;]*);";
    char *pat_lvs = "var c1Arr = new Array([^;]*);";
    char *pat_rvs = "var c2Arr = new Array([^;]*);";

    regcomp(&rx, pat_ids, REG_EXTENDED); 
    pos_of_match_in_html(pos_id, &rx, html);
    regcomp(&rx, pat_lvs, REG_EXTENDED); 
    pos_of_match_in_html(pos_lv, &rx, html);
    regcomp(&rx, pat_rvs, REG_EXTENDED); 
    pos_of_match_in_html(pos_rv, &rx, html);

    regfree(&rx);
}

void print_str_from_to(char *string, int from, int to) {
    for (int i = from; i < to; i++) putchar(string[i]);
    printf("\n");
}

void pos_of_match_in_html(substrpos_t *pos, regex_t *rx, char *html_data) {
    regmatch_t matches[2];
    if(regexec(rx, html_data, 2, matches, 0) == 0) {
        pos->start = matches[1].rm_so;
        pos->end = matches[1].rm_eo;
    } else {
        pos->start = 0;
        pos->end = 0;
    }
}

void add_next_vocab(vocab_data_t *vocab_to_add, substrpos_t *pos_id, substrpos_t *pos_lv, substrpos_t *pos_rv, char *html) {
    char *pat_id = "([0-9]+)";
    char *pat_v = "\x22([^\x22]*)\x22";
    regex_t rx_id, rx_v;
    regcomp(&rx_id, pat_id, REG_EXTENDED);
    regcomp(&rx_v, pat_v, REG_EXTENDED);

    j
    
    refree(rx_id);
    refree(rx_v);
}
