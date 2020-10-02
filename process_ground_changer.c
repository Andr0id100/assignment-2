#include "headers.h"
#include "linked_list.h"

void fg(char **args)
{
    args++;

    int job_number = strtol(args[0], NULL, 10);
    int pid = get_pid(job_number);

    if (pid == -1)
    {
        printf("Invalid Job Number\n");
    }
    else
    {
        signal(SIGTTOU, SIG_IGN);
        tcsetpgrp(STDIN_FILENO, pid);
        kill(pid, SIGCONT);
        int status;
        waitpid(pid, &status, WUNTRACED);
        tcsetpgrp(STDIN_FILENO, getpid());
        signal(SIGTTOU, SIG_DFL);
    }
}

void bg(char **args)
{
    args++;

    int job_number = strtol(args[0], NULL, 10);
    int pid = get_pid(job_number);

    if (pid == -1)
    {
        printf("Invalid Job Number\n");
    }
    else
    {
        kill(pid, SIGCONT);
    }
}