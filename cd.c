#include "headers.h"
#include "pathmanager.h"
#include "utils.h"

void cd(char **args)
{
    int count = count_args(args);

    if (count == 0)
    {
        go_home();
    }
    else if (count == 1)
    {
        if (!strcmp(args[0], "."))
        {
            // Do Nothing
        }
        else if (!strcmp(args[0], ".."))
        {
            move_back();
        }
        else if (!strcmp(args[0], "~"))
        {
            go_home();
        }
        else if (!strcmp(args[0], "-"))
        {
            past_pwd();
        }
        else
        {
            move_to(args[0]);
        }
    }
}