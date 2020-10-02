#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void handler();

int main() {
    
    signal(SIGTSTP, handler);
    while (1) {
        
    }
    return 0;
}

void handler() {
    printf("Inside Handler\n");
}