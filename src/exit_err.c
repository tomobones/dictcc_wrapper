#include <stdlib.h>
#include <stdio.h>

void exit_err(char *message) {
    fprintf(stderr, "Error: %s\n", message);
    exit(EXIT_FAILURE);
}
