#include "headers.h"

struct process {
    char* pid;
    unsigned long long time;
};


int compare(const void *a, const void *b) {
    struct process *element_1 = (struct process*) a;
    struct process *element_2 = (struct process*) b;
    return element_1->time - element_2->time;
    
}

int check_number(char* number) {
    for (int i=0;i<strlen(number);i++) {
        if (number[i] < '0' || number[i] > '9') {
            return 0;
        }
    }
    return 1;
}

void main() {
    int n = 1;
    while(1) {
        sleep(n);


        
        struct process list[300];
        
        DIR *directory;
        directory = opendir("/proc");
        struct dirent *entry;
        char* process_file = malloc(20 * sizeof(char));
        char* format = "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*lu %*lu %*lu %*lu %*lu %*lu %*ld %*ld %*ld %*ld %*ld %*ld %llu"; 
        entry = readdir(directory);
        unsigned long long time;
        int i = 0;
        while (entry != NULL) {
            if (check_number(entry->d_name)){
                sprintf(process_file, "/proc/%s/stat", entry->d_name);
                FILE* fp = fopen(process_file,"r");
                fscanf(fp, format, &time);
                fclose(fp);
                // printf("%s %llu\n", entry->d_name, time);
                list[i].pid = entry->d_name;
                list[i].time = time;
                i++;
            }
            entry = readdir(directory);
        }
        closedir(directory);
        qsort(list, i, sizeof(struct process), compare);
        printf("%s\n", list[i-1].pid);
    }
} 
