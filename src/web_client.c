#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <curl/curl.h>
#include <regex.h>
#include <string.h>

#include "data_center.h"

#define LANG_DEFAULT "deen"
#define URL_SEARCH "https://%s.dict.cc/?s=%s"
#define URL_LENGTH 256
#define FILE_COOKIE "/tmp/dictcc_cookie.txt"
#define FILE_HTML "/tmp/dictcc_html.txt"
#define BUFFER_MESSAGE 256

void exit_err(char *message);
void handle_curl_result(CURLcode result);
size_t data_handler_search(char* buffer, size_t itemsize, size_t nitems, void* ignorethis);

// add to vocab list
//
//vocabids="1451186,719355"
//vocablist="840649"
//url="https://www.dict.cc/mydict/ajax_add_entries_to_list.php?list_id=$vocablist&entry_ids=$vocabids"
//curl -vv --cookie cookies.txt $url


// login
//
//pw=XXXXXX
//url=https://secure.dict.cc/users/urc_logn.php
//#cred="is_utf8=1&hinz=voggo&kunz=$pw&ref=https://www.dict.cc/"
//cred="hinz=voggo&kunz=$pw"
//curl -X POST -vv --cookie-jar cookies.txt -d $cred $url > output.txt


// serach
//
//word=$1
//url="https://deen.dict.cc/?s=$word"
//#curl -b cookies.txt https://users.dict.cc/my-account/ > output.txt
//curl -cookie cookies.txt $url | grep -E "(idArr|c1Arr|c2Arr)"


// vocab lists
//
//url="https://my.dict.cc/" # get vocab list id
//curl -vv --cookie cookies.txt $url | grep -E "*my_vocab_lists\['*"


// public methods

bool scrape_vocabs_for_search(char* lang, char* search_string) {

    // test arguments
    bool need_to_free_lang = false;
    if (search_string == NULL) return false;
    if (lang == NULL) {
        lang = (char *)malloc(sizeof(char) * 5);
        strcpy(lang, LANG_DEFAULT); // default languages
        need_to_free_lang = true;
    }
    
    // generate search url
    char url[URL_LENGTH];
    sprintf(url, URL_SEARCH, lang, search_string);

    // get html
    CURL *curl_handle = curl_easy_init();
    if (!curl_handle) exit_err("Error: Coudn't initialize curl handle.\n");
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, data_handler_search);
    handle_curl_result(curl_easy_perform(curl_handle));
    curl_easy_perform(curl_handle);

    
    
    // clean up
    curl_easy_cleanup(curl_handle);
    if (need_to_free_lang == true) free(lang);
    return true;
}

bool login_user(char* user, char* pass) {
    return false;
}

bool scrape_vocablists_for_lang(char* lang) {
    return false;
}

void add_vocab_to_vocablist(int vocab_id, int list_id) {
}

void clean_up_session(void) {
    // delete cookie
}

// private methods

void handle_curl_result(CURLcode result) {
    if (result != CURLE_OK) {
        char message[BUFFER_MESSAGE];                                                          
        sprintf((char*)message, "No download possible: %s.", curl_easy_strerror(result));
        exit_err(message);
    }    
}

void exit_err(char *message) {
    fprintf(stderr, message);
    exit(EXIT_FAILURE);
}

size_t data_handler_search(char* buffer, size_t itemsize, size_t nitems, void* ignorethis) {
    for (int i = 0; i<nitems; i++) fprintf(stdout, "%c", buffer[i]);                                       
}
