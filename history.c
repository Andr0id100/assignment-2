#include "headers.h"
#include "pathmanager.h"

int count_entries(char*);
void history(char**);

void add_entry(char* line) {
    char file_path[128];
    sprintf(file_path, "%s/history.dat", get_home());


    int fp = open(file_path, O_CREAT | O_RDWR, 0600);
    char* buffer = malloc((10 * 1024)*sizeof(char));
    int file_size = lseek(fp, 0, SEEK_END);
    lseek(fp, 0, SEEK_SET);
    read(fp, buffer, file_size);
    int entries = count_entries(buffer);
    if (entries < 20) {
        write(fp, line, strlen(line));
    }
    else {
        buffer = strchr(buffer, '\n') + 1;
        close(fp);
        fp = open(file_path, O_WRONLY | O_TRUNC, 0600);
        write(fp, buffer, strlen(buffer));
        write(fp, line, strlen(line));

    }
    close(fp);
}

int count_entries(char* data) {
    int c = 0;
    int i=0;
    while (data[i] != '\0') {
        if (data[i] == '\n') {
            c++;
        }
        i++;
    }
    return c;
}

void history(char** args) {
    int count;
    if (args[0] == NULL) {
        count = 10;

    }
    else {
       count = strtol(args[0], NULL, 10);

       if (count > 10) {
           count = 10;
       }

    }  
    char file_path[128];
    sprintf(file_path, "%s/history.dat", get_home());

    int fp = open(file_path, O_CREAT | O_RDWR, 0600);
    char* buffer = malloc((10 * 1024)*sizeof(char));
    int file_size = lseek(fp, 0 , SEEK_END);
    lseek(fp, 0, SEEK_SET);
    read(fp, buffer, file_size);
    int entries = count_entries(buffer);
    if (entries <= count) {
        printf("%s", buffer);
    }
    else {
        int extra = entries - count;
        while (extra > 0) {
            buffer = strchr(buffer, '\n') + 1;
            extra--;
        }
        printf("%s", buffer);
    }
    close(fp);
}
