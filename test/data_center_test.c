#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "minunit.h"
#include "../include/data_center.h"

int tests_run = 0;
/* Created two function pointers to static functions which were failing to
 * compile because they were static. I have limited their visibility to just
 * this unit test by only including them if TEST_DATA_CENTER is defined. Also 
 * By doing it this way we avoid duplicating code
 */
extern bool (*fp_voclst_exists)(int);
extern bool (*fp_vocab_exists)(int);

char *test_vocab_add(void) {
    vocab_data_t *data1 = (vocab_data_t*) malloc(sizeof(vocab_data_t));;
    data1->nr = 1;
    data1->id = 234567;
    strcpy(data1->vl, "hello");
    strcpy(data1->vr, "Hallo");
    data1->is_marked = false;
    
    mu_assert("vocab_add: added 1st vocab, should return true",
              vocab_add(data1));

    vocab_data_t *data2 = (vocab_data_t*) malloc(sizeof(vocab_data_t));;
    data2->nr = 2;
    data2->id = 234568;
    strcpy(data2->vl, "hello");
    strcpy(data2->vr, "Hallo");
    data2->is_marked = false;

    mu_assert("vocab_add: added 2nd vocab, should return true",
              vocab_add(data2));

    return 0;
}

char *test_vocab_add_redundancy(void) {
    vocab_data_t *data1 = (vocab_data_t*) malloc(sizeof(vocab_data_t));;
    data1->nr = 1;
    data1->id = 234567;
    strcpy(data1->vl, "hello");
    strcpy(data1->vr, "Hallo");
    data1->is_marked = false;
    mu_assert("vocab_add: redundant id should return false",
              !vocab_add(data1));

    return 0;
}

char *test_vocab_exists(void) {
    /* Calling private function so declaring it here. */

    int id = 234567;
    int id_not = 334567;
    mu_assert("vocab_exists: for existing id should return true",
              (fp_vocab_exists)(id));
    mu_assert("vocab_exists: for nonexisting id should return false", 
              !(fp_vocab_exists)(id_not));

    return 0;
}

char *test_vocab_for_nr() {
    int id = 234567;
    int number = 1;
    vocab_data_t *data = vocab_for_nr(number);
    mu_assert("vocab_for_nr: shoud return data with adaquate id",
              data->id == id);

    return 0;
}

char *test_voclst_add(void) {
    voclst_data_t lstdata1; 
    lstdata1.nr = 1;
    lstdata1.id = 1999;
    strcpy(lstdata1.name, "english_list");
    mu_assert("voclst_add: should return true.", voclst_add(&lstdata1));

    voclst_data_t lstdata2;
    lstdata2.nr = 2;
    lstdata2.id = 2999;
    strcpy(lstdata2.name, "french_list");
    mu_assert("voclst_add: should return true.", voclst_add(&lstdata2));

    return 0;
}

char *test_voclst_add_redundancy(void) {
    voclst_data_t lstdata3;
    lstdata3.nr = 3;
    lstdata3.id = 1999;
    strcpy(lstdata3.name, "japanese_list");
    mu_assert("voclst_add: redundant id should return false.",
              !voclst_add(&lstdata3));

    return 0;
}

char *test_voclst_exists(void) {
    int id = 1999;
    int id_not = 2000;
    mu_assert("voclst_exists: for existing id should return true",
              (fp_voclst_exists)(id));
    mu_assert("voclst_exists: for nonexisting id should return false",
              !(fp_voclst_exists)(id_not));

    return 0;
}

char *test_voclst_for_nr(void) {
    int lnr = 2;
    int id = 2999;
    voclst_data_t *data = voclst_for_nr(lnr);
    mu_assert("vocab_for_nr: should return data with adaquate id",
              data->id == id);

    return 0;
}

char *all_tests() {
    mu_run_test(test_vocab_add);
    mu_run_test(test_vocab_add_redundancy);
    mu_run_test(test_vocab_for_nr);
    mu_run_test(test_vocab_exists);

    mu_run_test(test_voclst_add);
    mu_run_test(test_voclst_add_redundancy);
    mu_run_test(test_voclst_for_nr);
    mu_run_test(test_voclst_exists);

    data_clean_up();
    return 0;
}

int main(int argc, char** argv) {
    printf("\nTest: %s\n", argv[0]);
    char *test_message = all_tests();
    if (test_message != 0) printf("Test failed. Msg: %s\n", test_message);
    else printf("All tests in passed! (%i total test%c)\n\n", tests_run,
                (tests_run==1)?0:'s');

    return 0;
}
