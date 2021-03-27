#ifndef _DATA_CENTER_H_
#define _DATA_CENTER_H_

#include <stdbool.h>

#define BUFFER_VOCAB_SIZE 128

struct vd {
    int nr;
    int id;
    char vl[BUFFER_VOCAB_SIZE];
    char vr[BUFFER_VOCAB_SIZE];
    bool is_marked;
};
typedef struct vd vocab_data;

struct ld {
    int nr;
    int id;
    char name[BUFFER_VOCAB_SIZE];
    bool is_marked;
};
typedef struct ld voclst_data;

// vocab methods
bool vocab_add(const vocab_data *data);
vocab_data* vocab_for_nr(int nr);
void vocab_clean_up(void);
void vocab_print_all(void);
bool vocab_exists(int id);

// voclist methods
bool voclst_add(const voclst_data *data);
voclst_data* voclst_for_nr(int nr);
void voclst_clean_up(void);
void voclst_print_all(void);
bool voclst_exists(int id);

#endif
