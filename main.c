#include "headers.h"
#include "prompt.h"
#include "pathmanager.h"
#include "processmanager.h"
#include "input.h"

void children_exit();

int main() {
    // signal(SIGCHLD, children_exit);
    initialize_path();

    size_t len = 0;
    while (1) {
        prompt();
        input();
    }
    return 0;
}


void children_exit() {
    pid_t pid;
    int status;

    while ((pid=waitpid(-1, &status, WNOHANG)) > 0){
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            printf("\nProgram with pid %d exited normally\n", pid);
            return;
        }
        else {
            printf("\nProgram with pid %d exited abnormally", pid);
        }
    }

}

