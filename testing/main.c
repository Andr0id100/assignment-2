#include <unistd.h>
#include <stdio.h>



int main() {
    int n;

    char* args[10] = {"./hello", "One", "Two", NULL};
    while (1) {
        printf("Enter 1 for Printing hello\n");
        scanf("%d", &n);
        if (n == 1) {
            int response_code = execvp(args[0], args);
        }
    }
}