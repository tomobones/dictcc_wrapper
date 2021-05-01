#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#include "data_center.h"
#include "url_manager.h"
#include "web_client.h"
#include "err_exit.h"
#include "parser.h"
#include "user_interface.h"

#define LANG_DEFAULT "deen"
#define BUFFER_MAX 256

char *help_text = \
    "\n"
    "Options for dictcc\n\n"
    "\tsearch string without dash '-', several words separated by blanks\n"
    "-h\thelp\n"
    "-l\tparameter language codes: combinations of two country codes\n"
    "\tfor example 'deen', 'defr', 'enru', must include either 'de' or 'en'\n"
    "\tsupported country codes:\n"
    "\tde en sv is ru ro fr it sk pt nl hu fi la es bg hr no cs da tr pl eo sr el bs\n"
    "\n";

int main(int argc, char** argv) {

    // manage options
    bool option_help = false;
    bool option_lang = false;

    char lang_code[BUFFER_MAX] = "";

    int option;

    while ((option = getopt(argc, argv, "l:h")) != -1) {
        switch(option) {
            case 'h':
                option_help = true;
                break;
            case 'l':
                option_lang = true;
                strcpy(lang_code, optarg);
                break;
            case '?':
                err_exit("Invalid option: %c\n", optopt);
        }
    }
    
    // concatenate search string
    char search_string[BUFFER_MAX] = "";
    for (; optind < argc; optind++) {
        if (strcmp(search_string, "") == 0) {
            strcpy(search_string, argv[optind]);
        } else {
            char *aux_string = strcat(search_string, "+");
            strcpy(search_string, strcat(aux_string, argv[optind]));
        }
    }
    
    // print help string
    if (option_help) {
        printf(help_text);
        return 0;
    }
    
    // get url
    char url[BUFFER_MAX];
    url_for_search_and_lang(url, search_string , option_lang?lang_code:LANG_DEFAULT);

    // get html data
    struct MemoryStruct memory;
    memory.size = 0;
    memory.buffer = malloc(1);
    get_data_from_url(&memory, url);

    // parse data
    parse_vocabs_from_html(memory.buffer);

    // display
    init_ui();
    display_vocabs();
    cleanup_ui();

    // clean up
    data_clean_up();
    free(memory.buffer);

    return EXIT_SUCCESS;
}
