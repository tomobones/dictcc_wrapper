#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define BUFFER_SIZE 256

void err_exit(char *format, ...) {
    char message[BUFFER_SIZE];
    va_list args;

    va_start(args, format);
    vsprintf(message, format, args);
    fprintf(stderr, "Error: %s\n", message);

    va_end(args);
    exit(1);
}
