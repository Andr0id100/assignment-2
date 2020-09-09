#include "headers.h"


void pinfo(char** args) {
    char* pid = malloc(8 * sizeof(char));
    if (args[0] == NULL) {
        int id = getpid();
        sprintf(pid, "%d", id);
    }
    else {
        pid = args[0];
    }
    printf("pid -- %s\n", pid);

    char* file = malloc(20 * sizeof(char));
    sprintf(file, "/proc/%s/stat", pid);
    FILE* fp = fopen(file, "r");
    char status;
    char* line = malloc(1 * sizeof(char));
    size_t len = 1;
    getline(&line, &len, fp);
    fclose(fp);

    char* token = strtok(line, " ");
    int token_index = 1;

    for (int i=1;i <= 23; i++) {
        if (i == 3) {
            printf("Process Status -- %s\n", token);
        }
        else if(i == 23) {
            printf("Memory -- %s\n", token);
        }
        token = strtok(NULL, " ");

    }    
    char* executable_path = malloc(128 * sizeof(char));    
    sprintf(file, "/proc/%s/exe", pid);
    readlink(file, executable_path, 128);
    printf("Executable Path -- %s\n", executable_path);
    
}