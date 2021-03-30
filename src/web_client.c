#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <curl/curl.h>
#include <regex.h>
#include <string.h>

#include "web_client.h"
#include "exit_err.h"

#define LANG_DEFAULT "deen"
#define URL_SEARCH "https://%s.dict.cc/?s=%s"
#define URL_LENGTH 256
#define FILE_COOKIE "/tmp/dictcc_cookie.txt"
#define BUFFER_ERROR 256


// ________________________________________________________________
// private methods - declarations

void get_html_from_url(char *url);
void print_web_data(void);
const size_t data_handler_search(char* buffer, size_t itemsize, size_t nitems, void* ignorethis);
void parse_strings_from_html(char **ids, char **lvocabs, char **rvocabs);
void print_str_from_to(char *string, int from, int to);
void regex_match2string(regex_t rx, char** ptstrg);
void extract_data_from_strings(char *ids, char *lvocabs, char *rvocabs);


// ________________________________________________________________
// public methods - implementations

void get_data_from_url(struct MemoryStruct *webdata, char *url) {

    // curl - set and init vars
    char errbuffer[BUFFER_ERROR];
    webdata->size = 0;
    webdata->buffer = malloc(1);
    if (webdata->buffer == NULL) exit_err("Couldn't alloc var 'data.buffer' in 'web_client.c'");
    CURL *curl_handle = curl_easy_init();
    if (!curl_handle) exit_err("Coudn't initialize curl handle.");

    // curl - set options
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, data_handler_search);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)webdata);
    curl_easy_setopt(curl_handle, CURLOPT_ERRORBUFFER, errbuffer);

    // curl - retrieve data
    if (curl_easy_perform(curl_handle) != CURLE_OK) exit_err(errbuffer);

    // curl - cleanup
    curl_easy_cleanup(curl_handle);
}

// ________________________________________________________________
// private methods - implementations

const size_t data_handler_search(char* buffer, size_t itemsize, size_t nitems, void* mem_data) {
    int nbytes = (int)itemsize * (int)nitems;
     
    struct MemoryStruct *data = (struct MemoryStruct *) mem_data;
    data->buffer = realloc(data->buffer, data->size + nbytes + 1);
    if (data->buffer == NULL) exit_err("realloc() of MemoryStruct data.");
    memcpy(data->buffer + data->size, buffer, nbytes);
    data->size += nbytes;
    data->buffer[data->size] = 0;

    return (size_t)nbytes; 
}
