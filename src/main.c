#include <stdio.h>
#include <stdlib.h>

#include "data_center.h"
#include "url_manager.h"
#include "web_client.h"
#include "exit_err.h"
#include "parser.h"
#include "user_interface.h"

int main(int argc, char** argv) {

    // todo
    // parse arguments
    
    // get url
    char url[128];
    url_for_search_and_lang(url, argv[1], "deen");

    // get html data
    struct MemoryStruct memory;
    memory.size = 0;
    memory.buffer = malloc(1);
    get_data_from_url(&memory, url);

    // parse data
    parse_vocabs_from_html(memory.buffer);

    // print data
    //vocab_print_all();
    //vocab_clean_up();

    // display
    init_ui();
    display_vocabs();
    cleanup_ui();

    // clean up
    free(memory.buffer);

    return EXIT_SUCCESS;
}
