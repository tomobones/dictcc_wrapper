#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <curl/curl.h>
#include <regex.h>
#include <string.h>

#include "web_client.h"
#include "err_exit.h"


// ________________________________________________________________
// definitions

#define LANG_DEFAULT "deen"

#define URL_LENGTH 256
#define URL_SEARCH "https://%s.dict.cc/?s=%s"
#define URL_LOGIN "https://secure.dict.cc/users/urc_logn.php"
#define URL_LOGOUT "https://users.dict.cc/urc_logn.php?logout"
#define URL_LISTS "https://%s.my.dict.cc/"
#define URL_ADDLST "https://www.dict.cc/mydict/ajax_add_entries_to_list.php?list_id=%s&entry_ids=%s"

#define POST_LENGTH 256
#define POST_LOGIN "hinz=%s&kunz=%s"

#define FILE_COOKIE "/tmp/dictcc_cookie.txt"

#define BUFFER_ERROR 256


// ________________________________________________________________
// private methods - declarations

const size_t data_handler_mem(char* buffer, size_t itemsize, size_t nitems, void* ignorethis);


// ________________________________________________________________
// public methods - implementations

void get_data_from_url(struct MemoryStruct *webdata, char *url) {
    if (url == NULL) err_exit("No valid URL in function 'get_data_from_url'.");

    char errbuffer[BUFFER_ERROR];

    webdata->size = 0;
    webdata->buffer = malloc(1);
    if (webdata->buffer == NULL) err_exit("Couldn't alloc var 'data.buffer' in 'web_client.c'.");

    CURL *curl_handle = curl_easy_init();
    if (!curl_handle) err_exit("Coudn't initialize curl handle.");
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, data_handler_mem);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)webdata);
    curl_easy_setopt(curl_handle, CURLOPT_ERRORBUFFER, errbuffer);
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);                   

    if (curl_easy_perform(curl_handle) != CURLE_OK) err_exit(errbuffer);
    curl_easy_cleanup(curl_handle);
}

void open_session(char* user, char* passwd) {
    if (user == NULL || passwd == NULL) err_exit("No valid user or password passed.");

    char errbuffer[BUFFER_ERROR];

    struct MemoryStruct webdata;
    webdata.size = 0;
    webdata.buffer = malloc(1);

    char url[URL_LENGTH];
    sprintf(url, URL_LOGIN);

    char postfield[POST_LENGTH];
    sprintf(postfield, POST_LOGIN, user, passwd);

    CURL *curl_handle = curl_easy_init();
    if (!curl_handle) err_exit("Curl initialization.");                           
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);                            
    curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, postfield);               
    curl_easy_setopt(curl_handle, CURLOPT_POST, 1L);                             
    curl_easy_setopt(curl_handle, CURLOPT_COOKIEJAR, FILE_COOKIE);            
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, data_handler_mem);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)(&webdata));
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);                   
    curl_easy_setopt(curl_handle, CURLOPT_ERRORBUFFER, errbuffer);
                                                                                
    if (curl_easy_perform(curl_handle) != CURLE_OK) err_exit(errbuffer);
    curl_easy_cleanup(curl_handle);
}

void close_session(void) {
    char errbuffer[BUFFER_ERROR];

    struct MemoryStruct webdata;
    webdata.size = 0;
    webdata.buffer = malloc(1);

    CURL *curl_handle = curl_easy_init();
    if (!curl_handle) err_exit("Coudn't initialize curl handle.");
    curl_easy_setopt(curl_handle, CURLOPT_URL, URL_LOGOUT);
    curl_easy_setopt(curl_handle, CURLOPT_COOKIEFILE, FILE_COOKIE);            
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, data_handler_mem);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)(&webdata));
    curl_easy_setopt(curl_handle, CURLOPT_ERRORBUFFER, errbuffer);
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);                   

    if (curl_easy_perform(curl_handle) != CURLE_OK) err_exit(errbuffer);

    curl_easy_cleanup(curl_handle);
    remove(FILE_COOKIE);
}

void get_lists_for_lang (struct MemoryStruct *webdata, char *lang_code) {
    if (lang_code == NULL) err_exit("Language code not valid in function 'get_lists_for_lang'.");
    char errbuffer[BUFFER_ERROR];

    char url[URL_LENGTH];
    sprintf(url, URL_LISTS, lang_code);

    webdata->size = 0;
    webdata->buffer = malloc(1);
    if (webdata->buffer == NULL) err_exit("Couldn't alloc var 'data.buffer' in 'web_client.c'.");

    CURL *curl_handle = curl_easy_init();
    if (!curl_handle) err_exit("Curl initialization.");                           
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);                            
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, data_handler_mem);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)webdata);
    curl_easy_setopt(curl_handle, CURLOPT_COOKIEFILE, FILE_COOKIE);            
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);                   
    curl_easy_setopt(curl_handle, CURLOPT_ERRORBUFFER, errbuffer);
                                                                                
    if (curl_easy_perform(curl_handle) != CURLE_OK) err_exit(errbuffer);
                                                                                
    curl_easy_cleanup(curl_handle);
}

void add_vocabs_to_list(char* vocab_ids, char* list_id) {
    if (vocab_ids == NULL || list_id == NULL) err_exit("Vocabulary ID's and List ID's not valid in function 'add_vocab_to_list'.");

    char url[URL_LENGTH];
    sprintf(url, URL_ADDLST, list_id, vocab_ids);
    char errbuffer[BUFFER_ERROR];
    struct MemoryStruct webdata;
    webdata.size = 0;
    webdata.buffer = malloc(1);
    CURL *curl_handle = curl_easy_init();
    if (!curl_handle) err_exit("Curl initialization.");                           
                                                                                
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);                            
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, data_handler_mem);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)(&webdata));
    curl_easy_setopt(curl_handle, CURLOPT_COOKIEFILE, FILE_COOKIE);            
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);                   
    curl_easy_setopt(curl_handle, CURLOPT_ERRORBUFFER, errbuffer);
                                                                                
    if (curl_easy_perform(curl_handle) != CURLE_OK) err_exit(errbuffer);
                                                                                
    curl_easy_cleanup(curl_handle);
}


// ________________________________________________________________
// private methods - implementations

const size_t data_handler_mem(char* buffer, size_t itemsize, size_t nitems, void* mem_data) {
    struct MemoryStruct *data = (struct MemoryStruct *) mem_data;
    int nbytes = (int)itemsize * (int)nitems;

    data->buffer = realloc(data->buffer, data->size + nbytes + 1);
    if (data->buffer == NULL) err_exit("realloc() of MemoryStruct data.");
    memcpy(data->buffer + data->size, buffer, nbytes);
    data->size += nbytes;
    data->buffer[data->size] = 0;

    return (size_t)nbytes; 
}
