#include "headers.h"
#include "utils.h"
#include "linked_list.h"

void kjob(char** args) {
    args++;

    int job_number = strtol(args[0], NULL, 10);
    int sig = strtol(args[1], NULL, 10);

    int pid = get_pid(job_number);
    if (pid == -1) {
        printf("Invalid job number\n");
    }
    else {
        kill(pid, sig);
    }
}