#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "llist.h"
#include "task_util.h"

void file_open(char *file_path, struct Person *list)
{
    FILE *file = NULL;

    file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Unable to open file\n");
    } else {
        load_file(file, &list);
        printf("Initial List: \n");
        llist_print(list);
        fclose(file);
    }
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
    const int sz = 5;
    char buffer[sz];
    int c;
    while (1) {
        if (fgets(buffer, sz, stdin) == NULL) {
            printf("Wrong input!\n");
        } else if (sscanf(buffer, "%d", &task) != 1) {
            printf("Wrong input!\n");
        } else {
            return task;
        }
        consume_buffer(buffer);
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
        } else if (sscanf(buffer, "%" MAXV(INPUT_SIZE) "s", input) != 1) {
            printf("Wrong input!\n");
        } else {
            return input;
        }
        consume_buffer(buffer);
    }
}

void ask_address_input(char *line)
{
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
}