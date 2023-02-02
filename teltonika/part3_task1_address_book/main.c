#include "llist.h"
#define MAXV2(y) #y
#define MAXV(x) MAXV2(x)
#define SPACING 47

void load_file(FILE *file, struct Person **list);
void ask_input(struct Person **list);
void do_task(struct Person **list, int task);

int main(void)
{
    char file_path[30]= "addresses.csv";
    struct Person *list = NULL;
    FILE *file = NULL;

    file = fopen(file_path, "r");

    if (file == NULL){
        printf("Unable to open file\n");
        exit(1);

    }
    load_file(file, &list);
    printf("Initial List: ");
    llist_print(list);
    ask_input(list);
    llist_remove_all(list);
    fclose(file);
    return 0;
}

void load_file(FILE *file, struct Person **list)
{
    char line[128];
    while (fgets(line, sizeof(line), file)){
        if (strcmp(line, "\n") == 0)
            continue;
        
        struct Person *new = create_address_node(line);
        if (new != NULL){
            llist_add_end(list, new);
        }
    }
}

void print_possible()
{
    printf("%" MAXV(SPACING) "s\n", "Select task:");
    printf("%" MAXV(SPACING) "s\n", "Finish program - 1");
    printf("%" MAXV(SPACING) "s\n", "Print address book - 2");
    printf("%" MAXV(SPACING) "s\n", "Add new address to the end of list - 3");
    printf("%" MAXV(SPACING) "s\n", "Add new address to specified loation - 4");
    printf("%" MAXV(SPACING) "s\n", "Delete address at specified location - 5");
    printf("%" MAXV(SPACING) "s\n", "Delete all addresses - 6");
    printf("%" MAXV(SPACING) "s\n", "Find address by position - 7");
    printf("%" MAXV(SPACING) "s\n", "Find address by name, surname, email, phone - 8");
}
void ask_task(struct Person **list)
{
    print_possible();
    char newl;
    int task = 0;
    if (fscanf(stdin, "%d%c", &task, &newl) != 2 || newl != '\n'){
        printf("Wrong input!\n");
        ask_task(list);
        return;
    } else if (task > 8 && task < 1){
        printf("Task does not exist\n");
        ask_task(list);
        return;
    } else {
        do_task(list, task);
        exit(1);
    }
}

char *ask_address_input()
{
    return NULL;
}
void do_task(struct Person **list, int task)
{
    char input[128];
    struct Person *new = NULL;
    switch (task)
    {
        case 1:
            return;
            break;
        case 2:
            llist_print(list);
            break;
        case 3:
            input = ask_address_input();
            new = create_address_node(input);
            llist_add_end(*list, new);
            break;
        case 4:
            input = ask_address_input();
            new = create_address_node(input);
            llist_add_at(*list, new, task);
            break;
        case 5:
        
            break;
        case 6:
        
            break;
        case 7:
        
            break;
        case 8:
        
            break;
    }
}