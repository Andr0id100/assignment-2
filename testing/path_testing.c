#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char *line = malloc(1 * sizeof(char));
    ssize_t len = 1;

    char current_path[128];
    while (1)
    {
        printf("Input: ");

        getline(&line, &len, stdin);
        perror("Blah\n");
        chdir(line);
        getcwd(current_path, 128);
        printf("Current Directory: %s\n", current_path);
    }

    return 0;
}