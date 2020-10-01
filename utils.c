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

int count_occurences(char** args, char* token) {
    int c = 0;
    int i = 0;
    while (args[i] != NULL) {
        if (strcmp(args[i], token) == 0)
            c++;
        i++;
    }
    return c;
}

int count_args(char** args) {
    int c = 0;
    while (args[c] != NULL) {
        c++;
    }
    return c;
}