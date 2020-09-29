#include "headers.h"

int main(int argc, char** args) {
    args++;
    int i = 0;
    while (args[i] != NULL) {
        printf("%s ", args[i++]);
    }
    printf("\n");
}