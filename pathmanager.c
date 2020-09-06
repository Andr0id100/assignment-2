#include "headers.h"

char** homePath;
int homePathLength;
char** currentPath;
int currentPathLength;

int basePathHolds();
void moveTo(char*);
void moveBack();
void goHome();

void initializePath() {
    homePath = malloc(128 * sizeof(char*));
    currentPath = malloc(128 * sizeof(char*));

    char* path = getcwd(NULL, 0);
    char* token = strtok(path, "/");
    while (token != NULL) {
        homePath[homePathLength++] = token;
        currentPath[currentPathLength++] = token;
        
        token = strtok(NULL, "/");
    }
}
void printPath() {
    if (currentPathLength < homePathLength) {
        for (int i=0;i<currentPathLength;i++) {
            printf("/%s", currentPath[i]);
        }
    }
    else {
        if (basePathHolds()) {
            printf("~");
            if (currentPathLength > homePathLength) {
                for (int i=homePathLength;i<currentPathLength;i++) {
                    printf("/%s", currentPath[i]);
                }
            }
        }
        else {
            for (int i=0;i<currentPathLength;i++) {
               printf("/%s", currentPath[i]);
            }    
        }
         
    }
}

int basePathHolds() {
    if (currentPathLength < homePathLength) {
        return 0;
    }
    for (int i=0;i<homePathLength;i++) {
        if (strcmp(currentPath[i], homePath[i])){
            return 0;
        }
    }
    return 1;
}

void moveTo(char* path) {
    // Path is absolute
    char* finalPath;
    if (path[0] == '/'){
        finalPath = path;
    }
    // Path is relative
    else {
        int totalLength;
        int l = 0;
        while (l < currentPathLength) {
            totalLength += strlen(currentPath[l++]);
        }
        finalPath = malloc((totalLength + strlen(path) + l + 1) * sizeof(char));
        finalPath[0] = '\0';
        for (int i=0;i<currentPathLength;i++) {
            strcat(finalPath, "/");
            strcat(finalPath, currentPath[i]);
        }
        strcat(finalPath, "/");
        strcat(finalPath, path);
    }

    struct stat info;
    int response = stat(finalPath, &info);
    if (!response && S_ISDIR(info.st_mode)) {
        currentPathLength = 0;
        char* token = strtok(finalPath, "/");
        while (token != NULL) {
            currentPath[currentPathLength++] = token;
            token = strtok(NULL, "/");
        }
    }
    else {
        printf("Directory not found\n");
    }
}

void moveBack() {
    if (currentPathLength == 0) {
        printf("Cannot go any deeper\n");
    }
    else {
        currentPathLength--;
    }
}

void goHome() {
    for (int i=0;i<homePathLength;i++) {
        currentPath[i] = homePath[i];
    }
    currentPathLength = homePathLength;
}

void printCompletePath() {
    for (int i=0;i<currentPathLength;i++) {
        printf("/%s", currentPath[i]);
    }
}