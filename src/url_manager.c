#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define LANG_DEFAULT "deen"
#define LANG_BYTES 5
#define URL_SEARCH "https://%s.dict.cc/?s=%s"

bool url_for_search_and_lang(char* url, char* search, char* lang) {
    if (search == NULL || url == NULL) return false;
    sprintf(url, URL_SEARCH, LANG_DEFAULT, search);
    return true;
}
