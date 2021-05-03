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
#define URL_LISTS "https://my.dict.cc/"

#define POST_LENGTH 256
#define POST_LOGIN "hinz=%s&kunz=%s"

#define FILE_COOKIE "/tmp/dictcc_cookie.txt"

#define BUFFER_ERROR 256


// ________________________________________________________________
// private methods - declarations

void get_html_from_url(char *url);
void print_web_data(void);
const size_t data_handler_mem(char* buffer, size_t itemsize, size_t nitems, void* ignorethis);
const size_t data_handler_print(char* buffer, size_t itemsize, size_t nitems, void* ignorethis); 
void parse_strings_from_html(char **ids, char **lvocabs, char **rvocabs);
void print_str_from_to(char *string, int from, int to);
void regex_match2string(regex_t rx, char** ptstrg);
void extract_data_from_strings(char *ids, char *lvocabs, char *rvocabs);


// ________________________________________________________________
// public methods - implementations

void get_data_from_url(struct MemoryStruct *webdata, char *url) {

    char errbuffer[BUFFER_ERROR];
    webdata->size = 0;
    webdata->buffer = malloc(1);
    if (webdata->buffer == NULL) err_exit("Couldn't alloc var 'data.buffer' in 'web_client.c'");
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
    char errbuffer[BUFFER_ERROR];
    struct MemoryStruct webdata;
    webdata.size = 0;
    webdata.buffer = malloc(1);
    CURL *curl_handle = curl_easy_init();
    char url[URL_LENGTH];
    char postfield[POST_LENGTH];
    sprintf(url, URL_LOGIN);
    sprintf(postfield, POST_LOGIN, user, passwd);

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

void get_lists (struct MemoryStruct *webdata) {
    char errbuffer[BUFFER_ERROR];
    webdata->size = 0;
    webdata->buffer = malloc(1);
    if (webdata->buffer == NULL) err_exit("Couldn't alloc var 'data.buffer' in 'web_client.c'");
    CURL *curl_handle = curl_easy_init();
    if (!curl_handle) err_exit("Curl initialization.");                           
                                                                                
    curl_easy_setopt(curl_handle, CURLOPT_URL, URL_LISTS);                            
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, data_handler_mem);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)webdata);
    curl_easy_setopt(curl_handle, CURLOPT_COOKIEFILE, FILE_COOKIE);            
    curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);                   
    curl_easy_setopt(curl_handle, CURLOPT_ERRORBUFFER, errbuffer);
                                                                                
    if (curl_easy_perform(curl_handle) != CURLE_OK) err_exit(errbuffer);
                                                                                
    curl_easy_cleanup(curl_handle);
}

void add_vocabs_to_list(int* vocabs, int list) {
    // add to vocab list
    //vocabids="1451186,719355"
    //vocablist="840649"
    //url="https://www.dict.cc/mydict/ajax_add_entries_to_list.php?list_id=$vocablist&entry_ids=$vocabids"
    //curl -vv --cookie cookies.txt $url
}


// ________________________________________________________________
// private methods - implementations

const size_t data_handler_mem(char* buffer, size_t itemsize, size_t nitems, void* mem_data) {
    int nbytes = (int)itemsize * (int)nitems;
     
    struct MemoryStruct *data = (struct MemoryStruct *) mem_data;
    data->buffer = realloc(data->buffer, data->size + nbytes + 1);
    if (data->buffer == NULL) err_exit("realloc() of MemoryStruct data.");
    memcpy(data->buffer + data->size, buffer, nbytes);
    data->size += nbytes;
    data->buffer[data->size] = 0;

    return (size_t)nbytes; 
}

const size_t data_handler_print(char* buffer, size_t itemsize, size_t nitems, void* ignorethis) 
{                                                                               
    int nbytes = (int)itemsize * (int)nitems;
    for (int i = 0; i<nitems*itemsize; i++)                                     
    {                                                                           
        fprintf(stdout, "%c", buffer[i]);                                       
    }                                                                           
    return (size_t)nbytes; 
}    
