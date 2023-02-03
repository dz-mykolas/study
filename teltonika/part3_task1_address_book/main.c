#include "llist.h"
#define MAXV2(y) #y
#define MAXV(x) MAXV2(x)
#define SPACING 47
#define INPUT_SIZE 30

void load_file(FILE *file, struct Person **list);
void print_possible();
int ask_num();
void do_task(struct Person **list, int task);

int main(void)
{
    char file_path[30]= "addresses.csv";
    struct Person *list = NULL;
    FILE *file = NULL;

    file = fopen(file_path, "r");

    if (file == NULL) {
        printf("Unable to open file\n");
        exit(1);
    }
    load_file(file, &list);
    printf("Initial List: \n");
    llist_print(list);

    int task = 0;
    while (task != 1) {
        print_possible();
        task = ask_num();
        if (task > 8 || task < 1) {
            printf("Task does not exist!\n");
            continue;
        }
        do_task(&list, task);
    }

    llist_remove_all(&list);
    fclose(file);
    return 0;
}

void load_file(FILE *file, struct Person **list)
{
    char line[128];
    while (fgets(line, sizeof(line), file)) {
        if (strcmp(line, "\n") == 0)
            continue;
        
        struct Person *new = create_address_node(line);
        if (new != NULL) {
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

void consume_buffer(char *buffer)
{
    char *p;
    if (p = strchr(buffer, '\n')) {
        *p = '\0';
    } else {
        scanf("%*[^\n]");
        scanf("%*c");
    }
}
int ask_num()
{
    int task = 0;
    char buffer[3];
    int c;
    while (1) {
        if (fgets(buffer, 3, stdin) == NULL) {
            printf("Wrong input!\n");
        } else if (sscanf(buffer, "%d", &task) != 1) {
            printf("Wrong input!\n"); 
            consume_buffer(buffer);
        } else {
            return task;
        }
    }
    return task;
}

char *ask_input()
{
    char buffer[INPUT_SIZE + 2];
    char *input = malloc(sizeof(char) * INPUT_SIZE);
    int c;
    while (1) {
        if (fgets(buffer, INPUT_SIZE, stdin) == NULL) {
            printf("Wrong input!\n");
        } else {
            sscanf(buffer, "%" MAXV(INPUT_SIZE) "s \n", input);
            consume_buffer(buffer);
            return input;
        }
    }
}

char *ask_address_input()
{
    char *line = malloc(sizeof(char) * 128);
    char *name;
    char *surname;
    char *email;
    char *phone;

    printf("Enter name:\n");
    name = ask_input();
    printf("Enter surname:\n");
    surname = ask_input();
    printf("Enter email:\n");
    email = ask_input();
    printf("Enter phone:\n");
    phone = ask_input();
    snprintf(line, 128, "%s,%s,%s,%s", name, surname, email, phone);

    free(name);
    free(surname);
    free(email);
    free(phone);
    return line;
}

void do_task(struct Person **list, int task)
{
    char *input = NULL;
    struct Person *new = NULL;
    int pos = 0;
    switch (task) {
        case 2:
                printf("Current list:\n");
                llist_print(*list);
                break;
        case 3:
                input = ask_address_input();
                printf("New address: %s\n", input);
                new = create_address_node(input);
                llist_add_end(list, new);
                free(input);
                break;
        case 4:
                input = ask_address_input();
                printf("New address: %s\n", input);
                printf("Input address position: ");
                pos = ask_num();
                new = create_address_node(input);
                if (llist_add_at(list, new, pos) == 1) {
                    free(new);
                }
                free(input);
                break;
        case 5:
                printf("Input address position: ");
                pos = ask_num();
                llist_remove_at(list, pos);
                break;
        case 6:
                printf("Removed all!\n");
                llist_remove_all(list);
                break;
        case 7:
                //person_print();
                break;
        case 8:
                //person_print();
                break;
    }
}