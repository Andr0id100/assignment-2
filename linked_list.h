struct node {
    int job_number;
    char* name;
    int pid;

    struct node *next;

};

typedef struct node NODE;

void add_process(char*, int);
NODE* remove_process(int);
NODE* remove_process_with_pid(int);
void initialize_list();
void display_processes();
int get_pid(int);
void kill_all_children();