#include "headers.h"
#include "cd.h"
#include "ls.h"
#include "pwd.h"
#include "echo.h"
#include "pinfo.h"

int* bg_pids;
int bg_count;

void start_list() {
    bg_pids = malloc(64 * sizeof(int));
    bg_count = 0;
}

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

        for (int j=0;j<i;j++) {
            printf("%s\n", args[j]);
        }

        int id = fork();
        if (id == 0) {
            int return_value = execvp(args[0], args);    
            if (return_value == -1) {
                perror("Cannot run the command");
            }
        }

        else {
            if (bg) {
                // Do something here
            }

            else {
                int status;
                waitpid(id, &status, 0);
                // if (WIFEXITED(status)) {
                //     int exit_status = WEXITSTATUS(status);
                //     printf("Program exited successfully with status code %d\n", exit_status);
                // }
            }
        }
        
        // else {
        //     if (bg) {
        //         bg_pids[bg_count++] = id;
        //         printf("[%d] %d\n", bg_count, id);
        //     }
        //     else {
        //         int status;
        //         waitpid(id, &status, 0);
        //         printf("Test\n\n\n");
        //         if (WIFEXITED(status)) {
        //             int exit_status = WEXITSTATUS(status);
        //             printf("Programme exited with status %d\n\n\n", exit_status);

        //         }
        //     }
        // }
    }
    free(args);
}