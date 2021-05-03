#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <regex.h>
#include <string.h>

#include "data_center.h"
#include "parser.h"
#include "err_exit.h"


// ________________________________________________________________
// private vars - declaration

typedef struct SubstrPos {
    long start;
    long end;
} substr_pos_t;

// ________________________________________________________________
// private methods - declaration

void pos_of_match_in_html(substr_pos_t *pos, regex_t *rx, char *html_data);

// ________________________________________________________________
// public methods - implementation

bool parse_vocabs_from_html(char* html) {

    // set initial positions
    substr_pos_t pos_id, pos_vl, pos_vr;
    regex_t rx;
    char *pat_ids = "var idArr = new Array([^;]*);";
    char *pat_lvs = "var c1Arr = new Array([^;]*);";
    char *pat_rvs = "var c2Arr = new Array([^;]*);";
    regcomp(&rx, pat_ids, REG_EXTENDED); 
    pos_of_match_in_html(&pos_id, &rx, html);
    regcomp(&rx, pat_lvs, REG_EXTENDED); 
    pos_of_match_in_html(&pos_vl, &rx, html);
    regcomp(&rx, pat_rvs, REG_EXTENDED); 
    pos_of_match_in_html(&pos_vr, &rx, html);
    regfree(&rx);

    // loop retrieve of data
    char *pat_id = "([0-9]+)";
    char *pat_v = "\x22([^\x22]*)\x22";
    regex_t rx_id, rx_v;
    regcomp(&rx_id, pat_id, REG_EXTENDED);
    regcomp(&rx_v, pat_v, REG_EXTENDED);
    
    substr_pos_t pos_rltv;
    vocab_data_t vocab_to_add;
    vocab_to_add.nr = 0;
    vocab_to_add.is_marked = false;

    char aux_str[16];
    
    bool run_further = true;
    while (run_further) {
        vocab_to_add.nr++;
        
        // retrieve id
        pos_of_match_in_html(&pos_rltv, &rx_id, html + pos_id.start);
        if (pos_id.start + pos_rltv.start > pos_id.end) break;
        strncpy(aux_str, html + pos_id.start + pos_rltv.start, pos_rltv.end - pos_rltv.start);
        vocab_to_add.id = atol(aux_str);
        pos_id.start += pos_rltv.end;

        // retrieve left vocabulary
        pos_of_match_in_html(&pos_rltv, &rx_v, html + pos_vl.start);
        strncpy(vocab_to_add.vl, html + pos_vl.start + pos_rltv.start, pos_rltv.end - pos_rltv.start);
        vocab_to_add.vl[pos_rltv.end - pos_rltv.start] = '\0';
        pos_vl.start += (pos_rltv.end + 1);

        // retrieve right vocabulary
        pos_of_match_in_html(&pos_rltv, &rx_v, html + pos_vr.start);
        strncpy(vocab_to_add.vr, html + pos_vr.start + pos_rltv.start, pos_rltv.end - pos_rltv.start);
        vocab_to_add.vr[pos_rltv.end - pos_rltv.start] = '\0';
        pos_vr.start += (pos_rltv.end + 1);

        // add vocab to data
        if (vocab_to_add.id == 0) {
            vocab_to_add.nr--;
            continue;
        }

        vocab_add(&vocab_to_add);
    }
        
    regfree(&rx_id);
    regfree(&rx_v);
    
    return true;
}

void parse_voclsts_from_html(char* html) {
    //printf("%s\n", html);
    //return;

    regex_t rx_v;
    char* pat_v = "my_vocab_lists[[][']x([0-9]*)['][]]=[']([^']*)[']";
    regcomp(&rx_v, pat_v, REG_EXTENDED);
    regmatch_t matches[3];
    voclst_data_t voclst_to_add;
    voclst_to_add.nr = 0;
    voclst_to_add.is_marked = false;
    char aux_str[16];
    /* int nr; int id; char* name; bool is_marked */
    long string_offset = 0;
    while(regexec(&rx_v, html+string_offset, 3, matches, 0) == 0) {
        voclst_to_add.nr++;
        strncpy(aux_str, html + string_offset + matches[1].rm_so, matches[1].rm_eo - matches[1].rm_so);
        voclst_to_add.id = atol(aux_str);
        strncpy(voclst_to_add.name,\
                html + string_offset + matches[2].rm_so,\
                matches[2].rm_eo - matches[2].rm_so);
        voclst_add(&voclst_to_add); 
        string_offset += matches[2].rm_eo;
    }
}

// ________________________________________________________________
// private methods - implementation

void pos_of_match_in_html(substr_pos_t *pos, regex_t *rx, char *html_data) {
    regmatch_t matches[2];
    if(regexec(rx, html_data, 2, matches, 0) == 0) {
        pos->start = matches[1].rm_so;
        pos->end = matches[1].rm_eo;
    } else {
        pos->start = 0;
        pos->end = 0;
    }
}
