#include "headers.h"
#include "cd.h"
#include "ls.h"
#include "pwd.h"
#include "echo.h"
#include "pinfo.h"

//  
// 
// Check getopt
// 
// 
//
int* bg_pids;
int bg_count;

void start_list() {
    bg_pids = malloc(64 * sizeof(int));
    bg_count = 0;
}

void start_process(char** args) {
    
    if (strcmp(args[0], "cd") == 0) {
        cd(args+1);
    }
    else if (strcmp(args[0], "ls") == 0) {
        ls(args+1);
    }
    else if (strcmp(args[0], "pwd") == 0) {
        pwd();
    }
    else if (strcmp(args[0], "echo") == 0) {
        echo(args+1);
    }
    else if (strcmp(args[0], "pinfo") == 0) {
        pinfo(args+1);
    }
    else if (strcmp(args[0], "exit") == 0) {
        kill(getpid(), SIGINT);
    }
    else {
        int bg = 0;
        int i = 0;
        while (args[i] != NULL) {
            if (!strcmp(args[i], "&")) {
                bg = 1;
                while(args[i] != NULL) {
                    args[i] = args[i+1];
                    i++;
                }
                break;
            }
            i++;
        }

        int id = fork();
        if (id == 0) {
            int return_value = execvp(args[0], args);    
            if (return_value == -1) {
                perror("Cannot run the command");
            }
        }
        
        else {
            bg_pids[bg_count++] = id;
            if (bg) {
                printf("[%d] %d\n", bg_count, id);
            }
            else {
                wait(NULL);
            }
        }
    }
}