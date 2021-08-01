#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "err_exit.h"

#define URL_SEARCH "https://%s.dict.cc/?s=%s"

bool is_valid_lang_code (const char* lang) {
    if (lang[4] != '\0') return false;
    if ((lang[0] == 'd' && lang[1] == 'e') ||
        (lang[0] == 'e' && lang[1] == 'n') ||
        (lang[2] == 'd' && lang[3] == 'e') ||
        (lang[2] == 'e' && lang[3] == 'n')) return true;
    return false;
}

void url_search_and_lang(char* url, const char* search, const char* lang) {
    if (search == NULL) err_exit("No valid search string");
    if (url == NULL) err_exit("No valid url");
    if (!is_valid_lang_code(lang)) err_exit("No valid language code: %s\n", lang);

    // TODO calculate length of final string and use functions which do bounds
    sprintf(url, URL_SEARCH, lang, search);
}
