#include "headers.h"
#include "pathmanager.h"
//
// 
// The total thing
// 
// 

int process_flags(char**, int*, int*);
void show_list(char*, int, int);
char* get_permissions(struct stat info);

void ls(char** args) {
    int l_flag = 0;
    int a_flag = 0;

    if (process_flags(args, &l_flag, &a_flag) == -1) {
        printf("Invalid Flag(s)\n");
    }
    else {
        // Only one path
        if (args[0] == NULL) {
            show_list(".", l_flag, a_flag);
        }
        else if (args[1] == NULL) {
            show_list(args[0], l_flag, a_flag);
        }

        // Multiple Paths
        else {
            int i=0;
            while (args[i] != NULL) {
                printf("%s:\n", args[i]);
                show_list(args[i], l_flag, a_flag);
                printf("\n");
                i++;
            }
        }
    }
        
}


int process_flags(char** args, int* l_flag, int* a_flag) {
    int i = 0;
    while (args[i] != NULL) {
        if (args[i][0] == '-') {
            int j=1;
            while (args[i][j] != '\0') {
                switch (args[i][j]) {
                    case 'l':
                        *l_flag = 1;
                        break;
                    case 'a':
                        *a_flag = 1;
                        break;
                    default: 
                        return -1;
                }
                j++;
            }
            int temp = i;
            while (args[temp] != NULL) {
                args[temp] = args[temp+1];
                temp++;
            }
        }
        i++;
    }
    // Processed Sucessfully
    return 0;
}

void show_list(char* path, int l_flag, int a_flag){
    char* final_path = processed_path();
    // if (!strcmp(path, ".")) {
    //     final_path = getPath();
    // }
    // else if(!strcmp(path, "..")) {
    //     final_path = getPath();
    //     char* pointer = strrchr(final_path, '/');
    //     pointer[0] = '\0';
    // }
    // else if (!strcmp(path, "~")) {
    //     final_path = get_home();
    // }
    // else {
    //     final_path = path;
    // }

    DIR *directory;
    struct dirent *entry;

    directory = opendir(final_path);
    if (directory == NULL) {
        perror("Invalid input");
    }
    else {
        if (l_flag) {
            struct stat entry_info;
            char* entry_path = malloc(512);
            entry = readdir(directory);
            int total_block_size = 0;
            while (entry != NULL) {
                if (a_flag | (entry->d_name)[0] != '.'){
                    sprintf(entry_path, "%s/%s", final_path, entry->d_name);
                    stat(entry_path, &entry_info);
                    char* time = ctime(&(entry_info.st_mtime));
                    time = time + 4;
                    time[12] = '\0';
                    printf("%c%s%3ld %s %s %6ld %s %s\n",
                        S_ISDIR(entry_info.st_mode)? 'd' : '-', 
                        get_permissions(entry_info),
                        entry_info.st_nlink,
                        getpwuid(entry_info.st_uid)->pw_name,
                        getpwuid(entry_info.st_gid)->pw_name,
                        entry_info.st_size,
                        time,
                        entry->d_name
                    );
                    total_block_size += entry_info.st_blocks;
                }  
                entry = readdir(directory);
            }
            // printf("total %d\n", total_block_size);
        }
        else {
            entry = readdir(directory);
            while (entry != NULL) {
                if (a_flag | (entry->d_name)[0] != '.'){
                    printf("%s\n", entry->d_name);
                }
                entry = readdir(directory);

            }

        }
    }

}

char* get_permissions(struct stat info) {
        
    char* permissions = malloc(9 * sizeof(char));
    int permissionMasks[] = {
        S_IRUSR, S_IWUSR, S_IXUSR,
        S_IRGRP, S_IWGRP, S_IXGRP,
        S_IROTH, S_IWOTH, S_IXOTH};
    char* permisson_types = "rwx";
    for (int i=0;i<9;i++) {
        if (permissionMasks[i] & info.st_mode) {
            permissions[i] = permisson_types[i % 3];
        }
        else {
            permissions[i] = '-';
        }
    }
    permissions[8] = '\0';
    return permissions;
}