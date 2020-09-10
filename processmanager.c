#include "headers.h"
#include "cd.h"
#include "ls.h"
#include "pwd.h"
#include "echo.h"
#include "pinfo.h"
#include "history.h"
#include "newborn.h"

void start_process(char** args) {
    // Checking if the requested program is builtin and calling the relevant one
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
    else if (strcmp(args[0], "history") == 0) {
        history(args+1);
    }
    else if((strcmp(args[0], "nightswatch") == 0) && strcmp(args[3], "newborn") == 0) {
        newborn(args+1);
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
            if (bg) {
                setpgid(0, 0);
            }
            int return_value = execvp(args[0], args);    
            if (return_value == -1) {
                perror("Cannot run the command");
            }
        }

        else {
            
            if(!bg) {
                int status;
                waitpid(id, &status, 0);
            }
        }
    }
    free(args);
}