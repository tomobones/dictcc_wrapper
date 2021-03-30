#ifndef _WEB_CLIENT_H_
#define _WEB_CLIENT_H_

struct MemoryStruct {
    char *buffer;
    size_t size;
};

void get_data_from_url(struct MemoryStruct *webdata, char *url);

#endif
