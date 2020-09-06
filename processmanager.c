#include "headers.h"
#include "cd.h"
#include "ls.h"
#include "pwd.h"
#include "echo.h"

//  
// 
// Check getopt
// 
// 
//  

void start_process(char** args) {
    
    if (strcmp(args[0], "cd") == 0) {
        cd(args+1);
    }
    else if (strcmp(args[0], "ls") == 0) {
        // ls(args+1);
        printf("Execute ls\n");
    }
    else if (strcmp(args[0], "pwd") == 0) {
        pwd();
    }
    else if (strcmp(args[0], "echo") == 0) {
        echo(args+1);
    }
    else if (strcmp(args[0], "pinfo") == 0) {
        printf("Execute pinfo\n");
        // int pid = getpid();
        // printf("pid -- %d\n", pid);
        // char* processPath = malloc(128* sizeof(char));
        // char* linkPath = malloc(16*sizeof(char));
        // sprintf(linkPath, "/proc/%d/exe", pid);
        // int l = readlink(linkPath, processPath, 128);
        // processPath[l] = '\0';
        // printf("Executable path -- %s\n", processPath);
    }
    else if (strcmp(args[0], "exit") == 0) {
        kill(getpid(), SIGINT);
    }
    else {
        int id = fork();
        // int return_value;
        if (id == 0) {
            int return_value = execvp(args[0], args);    
            if (return_value == -1) {
                perror("Cannot run the command");
            }
        }
        wait(NULL);

    }
    
    
    
    // int id = fork();
    // int return_value;
    // if (id == 0) {
    //     return_value = execvp(args[0], args);    
    //     if (return_value == -1) {
    //         perror("Cannot run the command");
    //     }
    // }
    // wait(NULL);
}