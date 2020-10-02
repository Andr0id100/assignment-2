#include "headers.h"

struct node {
    int job_number;
    char* name;
    int pid;

    struct node *next;

};

typedef struct node NODE;

NODE *head;

void initialize_list() {
    head = NULL;
}

int job_counter = 1;

void add_process(char* name, int pid) {
// void add_item(int pid) {

    NODE *process = (struct node*)malloc(sizeof(struct node));
    process->job_number = job_counter++;
    process->name = name;
    process->pid = pid;
    
    if (head == NULL) {
        head = process;
    }
    else {
        NODE *temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = process;
        process->next = NULL;
    }
}

NODE* remove_process_with_pid(int pid) {
    if (head == NULL) {
        return NULL;
    }
    else {
        if (head->job_number == pid) {
            NODE *response = head;
            head = head->next;
            response->next = NULL;
            return response;
        }

        NODE *temp = head;
        NODE *parent = head;
        while (temp != NULL) {
            if (temp->job_number == pid) {
                NODE *response = temp;
                parent->next = temp->next;
                response->next = NULL;
                return response;
            }
            parent = temp;
            temp = temp->next;
        }
        return NULL;
    }
}

NODE* remove_process(int job_number) {
    if (head == NULL) {
        return NULL;
    }
    else {
        if (head->job_number == job_number) {
            NODE *response = head;
            head = head->next;
            response->next = NULL;
            return response;
        }

        NODE *temp = head;
        NODE *parent = head;
        while (temp != NULL) {
            if (temp->job_number == job_number) {
                NODE *response = temp;
                parent->next = temp->next;
                // response->next = NULL;
                return response;
            }
            parent = temp;
            temp = temp->next;
        }
        return NULL;
    }
}

void display() {
    NODE *temp = head;
    while (temp != NULL) {
        printf("%d->", temp->pid);
        temp=temp->next;
    }
    printf("NULL\n");
}

int is_stopped(int pid) {
    char* file = malloc(22 * sizeof(char));
    sprintf(file, "/proc/%d/stat", pid);

    FILE* fp = fopen(file, "r");

    if (fp == NULL)
        return -1;
    char status;

    fscanf(fp, "%*d %*s %c", &status);
    fclose(fp);


    return !(status == 'R' || status == 'S');

}

void display_processes() {
    NODE* temp = head;
    char* states[2] = {"Running", "Stopped"};
    while (temp != NULL) {
        int status = is_stopped(temp->pid);
        char* message;
        if (status == -1) {
            // message = "Dead"; 
            remove_process(temp->job_number);
        }
        else {
            message = states[status];
            printf("[%d] %s %s [%d]\n", temp->job_number, message, temp->name, temp->pid);
        }
        temp = temp->next;
    }
}

int get_pid(int job_number) {
    NODE* temp = head;
    while (temp != NULL) {
        if (temp->job_number == job_number) {
            return temp->pid;
        }
        temp = temp->next;
    }
    return -1;
}


void kill_all_children() {
    NODE* temp = head;
    while (temp != NULL) {
        kill(temp->pid, SIGKILL);
        temp = temp->next;
    } 
    head = NULL;

}