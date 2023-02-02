#include "llist.h"
#define DELIMITER ","
int SIZE = 0;

struct Person *create_address_node(char *string)
{
    char *name = strtok(string, DELIMITER);
    char *surname = strtok(NULL, DELIMITER);
    char *email = strtok(NULL, DELIMITER);
    char *phone = strtok(NULL, DELIMITER);

    // remove newline character
    char *ptr = strchr(phone, '\n');
    if(ptr){
        *ptr = '\0'; 
    }

    struct Person *person = create_node(name, surname, email, phone);
    return person;
}
struct Person *create_node(char *name, char *surname, char *email, char *phone)
{
    struct Person *p = (struct Person *) malloc(sizeof(struct Person));
    if (p == NULL){
        return NULL;
    }
    strcpy(p->name, name);
    strcpy(p->surname, surname);
    strcpy(p->email, email);
    strcpy(p->phone, phone);
    p->next = NULL;

    return p;
}

void llist_print(struct Person *list)
{
    struct Person *tmp = list;
    while (tmp != NULL){
        printf("%s %s %s %s\n", tmp->name, tmp->surname, tmp->email, tmp->phone);
        tmp = tmp->next;
    }
}

void llist_add_end(struct Person **list, struct Person *p)
{
    // check head
    struct Person *tmp = *list;
    if (tmp == NULL){
        *list = p;
        return;
    }

    while (tmp->next != NULL){
        tmp = tmp->next;
    }
    tmp->next = p;
    SIZE++;
}

int llist_add_at(struct Person **list, struct Person *p, int pos)
{
    if (pos > SIZE){
        printf("List is too small for specified position (Current Size: %d)", SIZE);
        return 1;
    }

    // check head
    struct Person *tmp = *list;
    if (tmp == NULL){
        if (pos != 0){
            printf("List has 0 elements, can not assign to position %d", pos);
            return 1;
        }
        *list = p;
        return 0;
    }

    struct Person *previous;
    while (tmp->next != NULL){
        previous = tmp;
        tmp = tmp->next;
    }
    previous->next = p;
    p->next = tmp;
    SIZE++;
}

int llist_remove_at(struct Person *list, int pos)
{
    if (pos > SIZE){
        printf("List is too small for specified position (Current Size: %d)", SIZE);
        return 1;
    }

    struct Person *tmp = list;
    int i = 0;
    while (tmp != NULL || i < pos){
        tmp = tmp->next;
        i++;
    }
    free(tmp);
    SIZE--;
    return 0;
}

void llist_remove_all(struct Person *list)
{
    struct Person *tmp = list;
    while (list != NULL){
        list = list->next;
        free(tmp);
        tmp = list;
        SIZE--;
    }
}

struct Person *llist_find_at(struct Person *list, int pos)
{
    if (pos > SIZE){
        printf("List is too small for specified position (Current Size: %d)", SIZE);
        return NULL;
    }

    struct Person *tmp = NULL;
    int i = 0;
    while (tmp != NULL || i < pos){
        tmp = tmp->next;
        i++;
    }
    return tmp;
}

struct Person *llist_find_by(struct Person *list, char *s)
{
    struct Person *tmp = NULL;
    int i = 0;
    while (tmp != NULL){
        tmp = list;
        if (strcmp(tmp->name, s) || strcmp(tmp->surname, s) || strcmp(tmp->email, s) || strcmp(tmp->phone, s) == 0){
            break;
        }
        i++;
    }
    return tmp;
}