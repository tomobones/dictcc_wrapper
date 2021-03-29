#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data_center.h"
#include "web_client.h"
#include "test.h"

void id_exists(int id) {
    if (vocab_exists(id)) {
        fprintf(stdout, "Vocab with id '%d' already exists.\n", id);
    } else {
        fprintf(stdout, "Vocab with id '%d' does not exists.\n", id);
    }
}

void test_data_center (void) {
    
    // vocab methods
    vocab_data data1;
    data1.nr = 1;
    data1.id = 123456;
    strcpy(data1.vl, "Hallo!");
    strcpy(data1.vr, "hello!");
    if (!vocab_add(&data1))
        printf("Data with id '%d' already exists", data1.id);
    
    vocab_data data2;
    data2.nr = 2;
    data2.id = 234567;
    strcpy(data2.vl, "Alligator");
    strcpy(data2.vr, "alligator");
    if (!vocab_add(&data2))
        printf("Data with id '%d' already exists", data2.id);

    vocab_data data3;
    data3.nr = 3;
    data3.id = 345678;
    strcpy(data3.vl, "Französisch");
    strcpy(data3.vr, "french");
    if (!vocab_add(&data3))
        printf("Data with id '%d' already exists", data3.id);

    vocab_print_all();

    id_exists(234567);
    id_exists(238567);

    int nr = 3;
    vocab_data *avail_data1 = vocab_for_nr(nr);
    if (avail_data1 == NULL) {
        printf("Coudn't retrieve data with nr '%d'.\n", nr);
    } else {
        printf("Retrieved data with id '%d'.\n", avail_data1->id);
    }

    vocab_clean_up();
    
    // voclst methods
    voclst_data lstdata1;
    lstdata1.nr = 1;
    lstdata1.id = 1999;
    strcpy(lstdata1.name, "english_list");
    if(!voclst_add(&lstdata1))
        printf("Data with id '%d' already exists", lstdata1.id);

    voclst_data lstdata2;
    lstdata2.nr = 2;
    lstdata2.id = 2999;
    strcpy(lstdata2.name, "french_list");
    if(!voclst_add(&lstdata2))
        printf("Data with id '%d' already exists", lstdata2.id);

    voclst_data lstdata3;
    lstdata3.nr = 3;
    lstdata3.id = 3999;
    strcpy(lstdata3.name, "japanese_list");
    if(!voclst_add(&lstdata3))
        printf("Data with id '%d' already exists", lstdata3.id);

    voclst_print_all();

    int lnr = 3;
    voclst_data *avail_ldata1 = voclst_for_nr(lnr);
    if (avail_ldata1 == NULL) {
        printf("Coudn't retrieve list with nr '%d'.\n", lnr);
    } else {
        printf("Retrieved list with id '%d'.\n", avail_ldata1->id);
    }

    voclst_clean_up();
}

void test_web_client (void) {
    scrape_vocabs_for_search("deen", "Schrank");
    web_client_clean_up();
}
