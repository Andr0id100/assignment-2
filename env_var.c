#include "headers.h"
#include "utils.h"

void set_env(char** args) {
    args++;
    int args_count = count_args(args);
    if (args_count > 2 || args_count < 1) {
        printf("Invalid number of arguments\n");
    }
    else {
        if (args[1] == NULL) {
            args[1] == "";
        }

        setenv(args[0], args[1], 1);
    }
}

void unset_env(char** args) {
    args++;
    int args_count = count_args(args);
    if (args_count != 1) {
        printf("Invalid number of arguments\n");
    }
    else {
        unsetenv(args[0]);
    }
}