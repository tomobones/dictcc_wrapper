#include <string.h>
#include <stdio.h>


#include "minunit.h"
#include "../src/data_center.h"

int tests_run = 0;

char *test_vocab_add(void) {
    vocab_data_t data;
    data.nr = 1;
    data.id = 1;
    strcpy(data.vl, "hello");
    strcpy(data.vr, "Hallo");
    data.is_marked = false;
    
    mu_assert("vacab_add: should return true", vocab_add(&data));
    return 0;
}

char *all_tests() {
    mu_run_test(test_vocab_add);
    return 0;
}

int main(void) {
    char *test_message = all_tests();
    if (test_message != 0) printf("Test failed. Msg: %s\n", test_message);
    else printf("All tests passed! (%i total tests)\n", tests_run);
}
/*
struct vd {
    int nr;
    int id;
    char vl[BUFFER_VOCAB_SIZE];
    char vr[BUFFER_VOCAB_SIZE];
    bool is_marked;
};
typedef struct vd vocab_data_t;

struct ld {
    int nr;
    int id;
    char name[BUFFER_VOCAB_SIZE];
    bool is_marked;
};

typedef struct ld voclst_data_t;
*/

// general methods
//void data_clean_up(void);

// vocab methods
//bool vocab_add(const vocab_data_t *data);
//vocab_data_t* vocab_for_nr(int nr);
//void vocab_print_all(void);
//bool vocab_exists(int id);

// voclist methods
//bool voclst_add(const voclst_data_t *data);
//voclst_data_t* voclst_for_nr(int nr);
//void voclst_print_all(void);
//bool voclst_exists(int id);
