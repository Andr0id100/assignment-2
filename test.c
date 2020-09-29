#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/wait.h>

int main () {
    // printf("Test\n");
    // char* line;
    // size_t len = 0;;
    // int l = getline(&line, &len, stdin);
    // line[l-1] = '\0';
    // // printf("%s %d", line, l);
    // char* token = strtok(line, " ");
    // // printf("%s", tokens[0]);
    // while (token != NULL) {
    //     printf("%s\n", token);
    //     token = strtok(NULL, " ");
    // }
    // char* path = (char*)malloc(128 * sizeof(char));
    // getcwd(path, 128);
    // printf("%s\n", path);
    // char* token = strtok(path, "/");
    // // printf("%s", tokens[0]);
    // while (token != NULL) {
    //     printf("%s\n", token);
    //     token = strtok(NULL, "/");
    // }
    // printf("%s\n", path);
    // int argc = 2;
    // char* argv[4] = {"a", "b", "c", "d"};
    // char* optstring = ":l:a";
    // printf("%d\n", getopt(argc, argv, optstring));
    
    int fd[2];
    pipe(fd);

    int stdin_backup = dup(STDIN_FILENO);
    int stdout_backup = dup(STDOUT_FILENO);

    
    dup2(fd[0], STDIN_FILENO);
    dup2(fd[1], STDOUT_FILENO);

    close(fd[0]);
    close(fd[1]);

 
        

    int pid = fork();
    
    if (pid == 0) {
        // close(fd[0]);
        // // dup2(fd[1], STDOUT_FILENO);
        // close(fd[1]);

        printf("This is a test statement\n");
        // dup2(stdout_backup, STDOUT_FILENO);

        // close(STDOUT_FILENO);
        // char* eof = {EOF, '\0'};
        // write(fd[1], eof, 2);
        // close(fd[1]);
    }
    else {
        //   sleep(1);
        // close(fd[1]);
        // // dup2(fd[0], STDIN_FILENO);
        // close(fd[0]);
        // char *line = malloc(1 * sizeof(char));
        char line[100];
        ssize_t len = 1;
        // getline(&line, &len, stdin);
        read(STDIN_FILENO, line, 80);
        // perror("Yo");
        fprintf(stderr, "FROM PARENT: %s", line);
        return 0;
    }

         
        

    // dup2(stdin_backup, STDIN_FILENO);
    // dup2(stdout_backup, STDOUT_FILENO);

    // wait(0);
    // return 0;

    // printf("Yosdhjfbsdhfbsdhg\n");
    // // close(fd[1]);
    // close(STDOUT_FILENO);
    // char *line = malloc(1 * sizeof(char));
    // ssize_t len = 1;
    // getline(&line, &len, stdin);

    // perror(line);
    
    // return 0; 


}
