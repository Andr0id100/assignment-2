#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{

    int fd[2];
    pipe(fd);

    if (fork() == 0)
    {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        char* args[2] = {"ls", NULL};
        execvp(args[0], args);
        // for (int i = 1; i <= 5; i++)
        // {
        //     printf("%d ", i);
        // }
        exit(0);
    }

    if (fork() == 0)
    {  
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);

        // char *line = malloc(1 * sizeof(char));
        // ssize_t len = 1;
        // getline(&line, &len, stdin); // read(0, buffer, 32);
        // printf("Child 2 read: %s\n", line);
        char* args[2] = {"wc", NULL};
        execvp(args[0], args);
        exit(0);
    }
    close(fd[0]);
    close(fd[1]);
    printf("Done\n");

    return 0;
}