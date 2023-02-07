#include "llist.h"
#include "main_helper.h"
#include "task_util.h"

void task_print(struct Person *list)
{
    printf("Current list:\n");
    llist_print(list);
}

void task_add_end(struct Person **list)
{
    char input[128];
    struct Person *new = NULL;

    ask_address_input(input);
    printf("New address: %s\n", input);
    new = create_address_node(input);
    llist_add_end(list, new);
}

void task_add_at(struct Person **list)
{
    char input[128];
    struct Person *new = NULL;
    int pos = 0;

    ask_address_input(input);
    printf("New address: %s\n", input);
    printf("Input address position: ");
    pos = ask_num();
    new = create_address_node(input);
    if (llist_add_at(list, new, pos) == 1) {
        free(new);
    }
}

void task_remove_at(struct Person *list)
{
    int pos = 0;

    printf("Input address position: ");
    pos = ask_num();
    llist_remove_at(&list, pos);
}

void task_remove_all(struct Person *list)
{
    printf("Removed all!\n");
    llist_remove_all(&list);
}   

void task_find_at(struct Person *list)
{
    int pos = 0;
    struct Person *new = NULL;

    printf("Input address position: ");
    pos = ask_num();
    if (pos < 0)
        printf("Position can not be less than 0\n");
    else if ((new = llist_find_at(list, pos)) != NULL)
        person_print(new);
}

void task_find_by(struct Person *list)
{
    char *input = NULL;
    struct Person *new = NULL;

    printf("Input exact name/surname/email/phone: ");
    input = ask_input();
    new = llist_find_by(list, input);
    if (new != NULL)
        person_print(new);
    else 
        printf("Address not found!\n");
    free(input);
}