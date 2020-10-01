struct node {
    int job_number;
    char* name;
    int pid;

    struct node *next;

};

typedef struct node NODE;

void add_process(int, char*, int);
NODE* remove_process(int);
void initialize_list();
void display_processes();