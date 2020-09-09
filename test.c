#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>

int main () {
    // printf("Test\n");
    // char* line;
    // size_t len = 0;;
    // int l = getline(&line, &len, stdin);
    // line[l-1] = '\0';
    // // printf("%s %d", line, l);
    // char* token = strtok(line, " ");
    // // printf("%s", tokens[0]);
    // while (token != NULL) {
    //     printf("%s\n", token);
    //     token = strtok(NULL, " ");
    // }
    // char* path = (char*)malloc(128 * sizeof(char));
    // getcwd(path, 128);
    // printf("%s\n", path);
    // char* token = strtok(path, "/");
    // // printf("%s", tokens[0]);
    // while (token != NULL) {
    //     printf("%s\n", token);
    //     token = strtok(NULL, "/");
    // }
    // printf("%s\n", path);
    int argc = 2;
    char* argv[4] = {"a", "b", "c", "d"};
    char* optstring = ":l:a";
    printf("%d\n", getopt(argc, argv, optstring));
    return 0; 
}