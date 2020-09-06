#include "headers.h"

void echo(char** args) {
    int i = 0;
    while (args[i] != NULL) {
        printf("%s ", args[i++]);
    }
    printf("\n");
}