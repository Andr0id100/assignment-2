#include "headers.h"
#include "cd.h"
#include "ls.h"
#include "pwd.h"
#include "echo.h"
#include "pinfo.h"
#include "history.h"
#include "newborn.h"
#include "utils.h"

int find_index(char**, char*);

void start_process(char** args) {
    int input_redirection_index;
    int output_redirection_overwrite_index;
    int output_redirect_append_index;

    input_redirection_index = find_index(args, "<");
    output_redirection_overwrite_index = find_index(args, ">");
    output_redirect_append_index = find_index(args, ">>");

    int stdin_backup = dup(STDIN_FILENO);
    int stdout_backup = dup(STDOUT_FILENO);



    if (input_redirection_index != -1) {
        int fd = open(args[input_redirection_index+1], O_RDONLY);
        if (fd < 0) {
            perror("Couldn't open file");
            return;
        }
        dup2(fd, STDIN_FILENO);
        remove_item(args, input_redirection_index);
    }

    if (output_redirection_overwrite_index != -1 || output_redirect_append_index != -1) {
        // Overwrite or append
        int o_or_a = output_redirection_overwrite_index != -1;
        int output_redirection_index = o_or_a ? output_redirection_overwrite_index : output_redirect_append_index;

        if (input_redirection_index != -1) {
            output_redirection_index--;
        }

        int fd = open(args[output_redirection_index+1], O_WRONLY | O_CREAT |  (o_or_a ? O_TRUNC : O_APPEND), 0644);
        if (fd < 0) {
            perror("Couldn't open file");
            return;
        }
        dup2(fd, STDOUT_FILENO);
        remove_item(args, output_redirection_index);
        remove_item(args, output_redirection_index);
    }




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
    dup2(stdin_backup, STDIN_FILENO);
    dup2(stdout_backup, STDOUT_FILENO);
    free(args);
}

int find_index(char** list, char* item) {
    int i=0;
    while (list[i] != NULL) {
        if (strcmp(list[i], item) == 0) {
            return i;
        }
        i++;
    }
    return -1;
}