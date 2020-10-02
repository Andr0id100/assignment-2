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
    // signal(SIGTSTP, ctrl_z);
    signal(SIGINT, ctrl_c);
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
    printf("\n\nHersdfsdgsfge\n\n");

    // int current_fg_id = tcgetpgrp(STDIN_FILENO);
    // if (current_fg_id != SHELL_ID)
    // {
    //     printf("\nSHELL: %d, PROCESS: %d\n", SHELL_ID, getpid());
    //     signal(SIGTTOU, SIG_IGN);
    //     tcsetpgrp(STDIN_FILENO, SHELL_ID);
    //     kill(SHELL_ID, SIGCONT);
    //     wait(0);
    //     signal(SIGTTOU, SIG_DFL);
    // }
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