#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "err_exit.h"

#define LANG_MIN_LEN 4
// All possible languages
#define LANG_CODES "deensvisrurofritskptnlhufilaesbghrnocsdatrpleosrelbs"
#define LANG_CODES_LEN 52
#define URL_SEARCH "https://%s.dict.cc/?s=%s"

bool is_valid_lang_code (const char* lang) {
    // Parameter check
    if (lang == NULL) {
        return false;
    } else if (strlen(lang) != LANG_MIN_LEN) {
        return false;
    }

    bool lang_1 = false;
    bool lang_2 = false;
    int i = 0;

    while (((lang_1 == false) || (lang_2 == false)) && (i < LANG_CODES_LEN)) {
        // Check first language code
        if ((lang_1 == false) &&
            (lang[0] == LANG_CODES[i]) &&
            (lang[1] == LANG_CODES[i + 1])) {

            lang_1 = true;
        }
        
        // Check for second language code
        if ((lang_2 == false) &&
            (lang[2] == LANG_CODES[i]) &&
            (lang[3] == LANG_CODES[i + 1])) {
            
            lang_2 = true;
        }

        // Increment i by 2 to get next country code
        i += 2;
    }

    if ((lang_1 == true) && (lang_2 == true)) {
        return true;
    }

    return false;
}

void url_search_and_lang(char* url, const char* search, const char* lang) {
    if (search == NULL) err_exit("No valid search string");
    if (url == NULL) err_exit("No valid url");
    if (!is_valid_lang_code(lang)) err_exit("No valid language code: %s\n", lang);
    char str[256] = "";
    // TODO calculate length of final string and use functions which do bounds
    // checking i.e. strncpy
    sprintf(str, URL_SEARCH, lang, search);
    strcpy(url, str);
}
