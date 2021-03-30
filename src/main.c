#include <stdio.h>
#include <stdlib.h>

#include "data_center.h"
#include "url_manager.h"
#include "web_client.h"
#include "exit_err.h"
#include "parser.h"

int main(int argc, char** argv) {
    
    // get url
    char url[128];
    url_for_search_and_lang(url, "Auto", NULL);

    // get html data
    struct MemoryStruct memory;
    memory.size = 0;
    memory.buffer = malloc(1);
    get_data_from_url(&memory, url);

    // parse data
    parse_vocabs_from_html(memory.buffer);

    // clean up
    free(memory.buffer);

    return EXIT_SUCCESS;
}
