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
    "  ----------------------------------------------------------\n"
    "                     HELP TEXT - DICTCC\n"
    "  ----------------------------------------------------------\n"
    "\n"
    "  This is an inofficial client for 'www.dict.cc'\n"
    "  Add search strings to the command without dash '-',\n"
    "  several words are separated by blanks\n"
    "  \n"
    "  Options:\n"
    "  '-h' displays this help text\n"
    "  '-l <language code>' specifies laguages\n"
    "  \n"
    "  The language code is a combinations of two country codes.\n"
    "  Default value is 'deen' for translation german <> english\n"
    "  must include either 'de' or 'en'.\n"
    "  Supported country codes are:\n"
    "  \n"
    "  'de', 'en', 'sv', 'is', 'ru', 'ro', 'fr', 'it', 'sk',\n"
    "  'pt', 'nl', 'hu', 'fi', 'la', 'es', 'bg', 'hr', 'no',\n"
    "  'cs', 'da', 'tr', 'pl', 'eo', 'sr', 'el', 'bs'\n"
    "  \n"
    "  Examples:\n"
    "  'dictcc car race'\n"
    "  'dictcc -l defr bicyclette'\n"
    "  'dictcc -l enru bicycle',\n"
    "  \n"
    "  Keybindings:\n"
    "  'q': exit, 'j': up, 'k': down, SPACE to select,\n"
    "  'a': to add selected vocabs to a list\n"
    "  \n"
    "  ----------------------------------------------------------\n"
    "  \n";

int main(int argc, char** argv) {

    // manage options
    bool option_help = false;
    bool option_lang = false;
    char lang_code[BUFFER_MAX] = "";
    int option;
    
    if (argc == 1) option_help = true;
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
    url_search_and_lang(url, search_string , option_lang?lang_code:LANG_DEFAULT);

    // get html data
    struct MemoryStruct memory;
    memory.size = 0;
    memory.buffer = malloc(1);
    get_data_from_url(&memory, url);

    // parse data
    parse_vocabs_from_html(memory.buffer);

    // user interface
    init_ui();
    if (loop_vocabs_ui()) {
        
        // query username and password
        char username[BUFFER_MAX];
        char password[BUFFER_MAX];
        get_user_passwd(username, password);
        
        open_session(username, password);

        // read lists from account
        struct MemoryStruct mem;
        mem.size = 0;
        mem.buffer = malloc(1);
        get_lists_for_lang(&mem, option_lang?lang_code:LANG_DEFAULT);
        parse_voclsts_from_html(mem.buffer);

        // display lists, choose one
        //char* list_id_str = "994698"; //TestTerminal
        char list_id_str[BUFFER_MAX];
        get_voclst(list_id_str);

        // add vocabs to list
        char vocab_ids_str[BUFFER_MAX];
        vocabs_marked(vocab_ids_str);
        add_vocabs_to_list(vocab_ids_str, list_id_str);
        close_session();
    }

    // clean up
    cleanup_ui();
    data_clean_up();
    free(memory.buffer);

    return EXIT_SUCCESS;
}
