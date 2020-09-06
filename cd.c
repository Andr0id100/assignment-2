#include "headers.h"
#include "pathmanager.h"

int count_args(char**);

void cd(char ** args) {
    int count = count_args(args);

    if (count == 0) {
            // printf("Blank\n");
            goHome();
        }
    else if (count == 1) {
        if (!strcmp(args[0], ".")) {
            
        }
        else if(!strcmp(args[0], "..")){
            moveBack();
        }
        else if(!strcmp(args[0], "~")) {
            goHome();
        }
        else {
            moveTo(args[0]);
        }
    }

}


int count_args(char** args) {
    int c = 0;
    while (args[c] != NULL) {
        c++;
    }
    return c;
}