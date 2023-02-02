#include "llist.h"
#define MAXV2(y) #y
#define MAXV(x) MAXV2(x)
#define SPACING 47
#define INPUT_SIZE 30

void load_file(FILE *file, struct Person **list);
void ask_task(struct Person **list);
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
    printf("Initial List: \n");
    llist_print(list);

    ask_task(&list);

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
    printf("%" MAXV(SPACING) "s\n", "Exit program - 1");
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
    char buffer[3];
    int c;
    while (1){
        if (fgets(buffer, 3, stdin) == NULL){
            printf("Wrong input!\n");
        } else if (sscanf(buffer, "%d", &task) != 1){
            printf("Wrong input!\n");
            // TODO: Understand
            /*
            char *p;
            if(p=strchr(buffer, '\n')){//check exist newline
                *p = 0;
            } else {
                scanf("%*[^\n]");scanf("%*c");//clear upto newline
            }
            */ https://stackoverflow.com/a/38768287/15218705
        } else {
            do_task(list, task);
            break;
        }
    }
        /*
        if (fscanf(stdin, "%d%c", &task, &newl) != 2 || newl != '\n'){
            printf("Wrong input!\n");
            goto ask_task;
        } else if (task > 8 || task < 1){
            printf("Task does not exist\n");
            ask_task(list);
        } else if (task == 1){
            printf("Exiting program\n");
        }
        else {
            do_task(list, task);
        }
        */
}

char *ask_address_input()
{
    char *line = malloc(sizeof(char) * 128);
    char buffer[INPUT_SIZE];
    
    char *name;
    char *surname;
    char *email;
    char *phone;
    
    // add goto if sscanf() returns less than 1 to repeat asking
    ask_name:
    printf("Enter name:\n");
    fgets(buffer, INPUT_SIZE, stdin);
    //name = strtok(buffer, " \n");
    //printf("%li\n", sizeof(name));
    printf("%li\n", sizeof(buffer));
    snprintf(line, 128, "%s", buffer);

    /*
    printf("Enter surname:\n");
    fgets(buffer, INPUT_SIZE, stdin);
    surname = strtok(buffer, " \n");
    printf("%li\n", sizeof(surname));

    printf("Enter surname:\n");
    fgets(buffer, INPUT_SIZE, stdin);
    email = strtok(buffer, " \n");
    printf("%li\n", sizeof(email));
    
    printf("Enter surname:\n");
    fgets(buffer, INPUT_SIZE, stdin);
    phone = strtok(buffer, " \n");
    printf("%li\n", sizeof(phone));
    */
    

    /*
    fscanf(stdin, "%" MAXV(INPUT_SIZE) "[^\n]", name);
    printf("Enter surname:\n");
    fscanf(stdin, "%" MAXV(INPUT_SIZE) "[^\n]", surname);
    printf("Enter email:\n");
    fscanf(stdin, "%" MAXV(INPUT_SIZE) "[^\n]", email);
    printf("Enter phone:\n");
    fscanf(stdin, "%" MAXV(INPUT_SIZE) "[^\n]", phone);
    */
    
    //snprintf(line, 128, "%s,%s,%s,%s", buffer, surname, email, phone);
    return line;
}
void do_task(struct Person **list, int task)
{
    char *input = NULL;
    struct Person *new = NULL;
    switch (task)
    {
        case 2:
                printf("Current list:\n");
                llist_print(*list);
                break;
        case 3:
                input = ask_address_input();
                printf("%s\n", input);
                //new = create_address_node(input);
                //llist_add_end(list, new);
                free(input);
                break;
        /*
        case 4:
            input = ask_address_input();
            new = create_address_node(input);
            llist_add_at(list, new, task);
            break;
        case 5:
        
            break;
        case 6:
        
            break;
        case 7:
        
            break;
        case 8:
        
            break;
        */
    }
}