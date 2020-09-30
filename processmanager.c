#include "headers.h"
#include "cd.h"
#include "ls.h"
#include "pwd.h"
#include "echo.h"
#include "pinfo.h"
#include "history.h"
#include "newborn.h"
#include "utils.h"

int find_index(char **, char *);
void redirect_io(char **);
void restore_io();
void execute_process(char **, int[][2], int);
void close_pipes(int[][2], int);
int count_args(char**);

int stdin_backup;
int stdout_backup;

void start_process(char **args)
{   
    stdin_backup = dup(STDIN_FILENO);
    stdout_backup = dup(STDOUT_FILENO);

    int pipe_count = count_occurences(args, "|") + 2;
    int fdes[pipe_count][2];

    for (int i = 0; i < pipe_count; i++)
    {
        pipe(fdes[i]);
    }

    dup2(STDIN_FILENO, fdes[0][0]);
    dup2(STDOUT_FILENO, fdes[pipe_count - 1][1]);

    close(fdes[0][1]);
    close(fdes[pipe_count-1][0]);


    int i = 0;
    int command_start = 0;

    int pipe_index = 0;

    while (args[i] != NULL)
    {
        if (strcmp(args[i], "|") == 0)
        {   
            args[i] = NULL;
            // redirect_io(args);
            execute_process(args, fdes, pipe_index);
            restore_io();
            args = args+i+1;
            i=0;
            pipe_index++;
        }
        i++;
    }
    // redirect_io(args);
    execute_process(args, fdes, pipe_index == 0 ? -1 : pipe_index);
    restore_io();

    close_pipes(fdes, pipe_count);

    wait(0);

    for (int i=1;i<=pipe_count-1;i++)
        wait(0);
}

int find_index(char **list, char *item)
{
    int i = 0;
    while (list[i] != NULL)
    {
        if (strcmp(list[i], item) == 0)
        {
            return i;
        }
        i++;
    }
    return -1;
}

void redirect_io(char **args)
{
    int input_redirection_index;
    int output_redirection_overwrite_index;
    int output_redirect_append_index;

    input_redirection_index = find_index(args, "<");
    output_redirection_overwrite_index = find_index(args, ">");
    output_redirect_append_index = find_index(args, ">>");

    if (input_redirection_index != -1)
    {
        int fd = open(args[input_redirection_index + 1], O_RDONLY);
        if (fd < 0)
        {
            perror("Couldn't open file");
            return;
        }
        dup2(fd, STDIN_FILENO);
        remove_item(args, input_redirection_index);
    }

    if (output_redirection_overwrite_index != -1 || output_redirect_append_index != -1)
    {
        // Overwrite or append
        int o_or_a = output_redirection_overwrite_index != -1;
        int output_redirection_index = o_or_a ? output_redirection_overwrite_index : output_redirect_append_index;

        if (input_redirection_index != -1)
        {
            output_redirection_index--;
        }

        int fd = open(args[output_redirection_index + 1], O_WRONLY | O_CREAT | (o_or_a ? O_TRUNC : O_APPEND), 0644);
        if (fd < 0)
        {
            perror("Couldn't open file");
            return;
        }
        dup2(fd, STDOUT_FILENO);
        remove_item(args, output_redirection_index);
        remove_item(args, output_redirection_index);
    }
}

void restore_io()
{
    dup2(stdin_backup, STDIN_FILENO);
    dup2(stdout_backup, STDOUT_FILENO);
}

void execute_process(char **args, int fdes[][2], int pipe_index)
{
    close(fdes[pipe_index][1]);

    dup2(fdes[pipe_index][0], STDIN_FILENO);
    dup2(fdes[pipe_index + 1][1], STDOUT_FILENO);

    close(fdes[pipe_index][0]);
    close(fdes[pipe_index + 1][1]);

    redirect_io(args);


    if (strcmp(args[0], "cd") == 0)
    {
        cd(args + 1);
    }
    else if (strcmp(args[0], "pinfo") == 0)
    {
        pinfo(args + 1);
    }
    else if (strcmp(args[0], "pwd") == 0)
    {
        pwd();
    }
    else if (strcmp(args[0], "exit") == 0)
    {
        kill(getpid(), SIGINT);
    }
    else if (strcmp(args[0], "history") == 0)
    {
        history(args + 1);
    }
    else if ((strcmp(args[0], "nightswatch") == 0) && strcmp(args[3], "newborn") == 0)
    {
        newborn(args + 1);
    }
    else if (strcmp(args[0], "ls") == 0)
    {
        ls(count_args(args), args);
    }
    else if (strcmp(args[0], "echo") == 0)
    {
        echo(count_args(args), args);
    }
    else
    {
        int bg = 0;
        int i = 0;
        while (args[i] != NULL)
        {
            if (!strcmp(args[i], "&"))
            {
                bg = 1;
                while (args[i] != NULL)
                {
                    args[i] = args[i + 1];
                    i++;
                }
                break;
            }
            i++;
        }

        int id = fork();
        if (id == 0)
        {   
            if (bg)
            {
                setpgid(0, 0);
            }
            int return_value = execvp(args[0], args);
            if (return_value == -1)
            {
                perror("Cannot run the command");
            }
        }

        else
        {
            if (!bg && pipe_index == -1)
            {
                int status;
                waitpid(id, &status, 0);
            }
        }
    }
    close(fdes[pipe_index][0]);
    close(fdes[pipe_index+1][1]);
}


void close_pipes(int fdes[][2], int pipe_count) {
    for (int i=0;i<pipe_count;i++) {
        int i1 = close(fdes[i][0]);
        int i2 = close(fdes[i][1]);
        // if (i1 || i2)
        //     fprintf(stderr, "Bad FD %d %d %d\n", i, i1, i2);
    }
}
