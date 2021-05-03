#ifndef WEB_CLIENT_H
#define WEB_CLIENT_H

struct MemoryStruct {
    char *buffer;
    size_t size;
};

void get_data_from_url(struct MemoryStruct *webdata, char *url);
void get_lists_for_lang (struct MemoryStruct *webdata, char *lang_code);
void add_vocabs_to_list(int* vocabs, int list);

void open_session(char* user, char* passwd);
void close_session(void);

#endif
