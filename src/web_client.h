#ifndef WEB_CLIENT_H
#define WEB_CLIENT_H

struct MemoryStruct {
    char *buffer;
    size_t size;
};

void get_data_from_url(struct MemoryStruct *webdata, char *url);

#endif
