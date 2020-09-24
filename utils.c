#include "headers.h"


void remove_item(char** args, int index) {
    while (args[index] != NULL) {
        args[index] = args[index+1];
        index++;
    }
}

void print_args(char** args) {
    int i = 0;
    while (args[i] != NULL) {
        printf("%s\n", args[i++]);
    }
}