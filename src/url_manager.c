#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define LANG_BYTES 5
#define URL_SEARCH "https://%s.dict.cc/?s=%s"

bool url_for_search_and_lang(char* url, const char* search, const char* lang) {
    if (search == NULL || url == NULL) return false;
    char str[256];
    sprintf(str, URL_SEARCH, lang, search);
    strcpy(url, str);
    return true;
}
