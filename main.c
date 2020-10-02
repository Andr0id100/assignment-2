#include "headers.h"
#include "prompt.h"
#include "pathmanager.h"
#include "processmanager.h"
#include "input.h"
#include "linked_list.h"

void ctrl_z();
void ctrl_c();
int SHELL_ID;

int main()
{
    SHELL_ID = getpid();
    signal(SIGCHLD, SIG_IGN);
    signal(SIGINT, ctrl_c);
    signal(SIGTSTP, ctrl_z);

    setpgid(0, 0);

    initialize_path();
    initialize_list();

    size_t len = 0;
    while (1)
    {
        prompt();
        input();
    }
    return 0;
}

void ctrl_z()
{
    printf("\n");
}

void ctrl_c()
{
    int current_fg_id = tcgetpgrp(STDIN_FILENO);
    if (current_fg_id != SHELL_ID)
    {
        kill(current_fg_id, SIGINT);
        tcsetpgrp(STDIN_FILENO, SHELL_ID);
    }
    else
    {
        printf("\n");
    }
}