#include "llist.h"
#define DELIMITER ","

struct Person *create_address_node(char *string)
{
    char *name = strtok(string, DELIMITER);
    char *surname = strtok(NULL, DELIMITER);
    char *email = strtok(NULL, DELIMITER);
    char *phone = strtok(NULL, DELIMITER);

    // remove newline character
    char *ptr = strchr(phone, '\n');
    if(ptr) {
        *ptr = '\0'; 
    }

    struct Person *person = create_node(name, surname, email, phone);
    return person;
}
struct Person *create_node(char *name, char *surname, char *email, char *phone)
{
    struct Person *p = (struct Person *) malloc(sizeof(struct Person));
    if (p == NULL) {
        return NULL;
    }
    strcpy(p->name, name);
    strcpy(p->surname, surname);
    strcpy(p->email, email);
    strcpy(p->phone, phone);
    p->next = NULL;

    return p;
}

int get_size(struct Person *list)
{   
    struct Person *tmp = list;
    int i = 0;
    while (tmp != NULL) {
        tmp = tmp->next;
        i++;
    }
    return i;
}

void llist_print(struct Person *list)
{
    struct Person *tmp = list;
    while (tmp != NULL) {
        printf("%s %s %s %s\n", tmp->name, tmp->surname, tmp->email, tmp->phone);
        tmp = tmp->next;
    }
}

void llist_add_end(struct Person **list, struct Person *p)
{
    // check head
    struct Person *tmp = *list;
    if (tmp == NULL) {
        *list = p;
        return;
    }

    while (tmp->next != NULL) {
        tmp = tmp->next;
    }
    tmp->next = p;
}

int llist_add_at(struct Person **list, struct Person *p, int pos)
{
    struct Person *tmp = *list;
    if (pos == 0) {
        if (tmp == NULL) {
            *list = p;
        } else {
            p->next = *list;
            *list = p;
        }
        return 0;
    }

    if (tmp == NULL) {
        printf("List has 0 elements, can not assign to position %d", pos);
        return 1;
    } else {
        struct Person *previous;
        int i = 0;
        while (tmp != NULL && i < pos) {
            previous = tmp;
            tmp = tmp->next;
            i++;
        }
        if (i < pos) {
            printf("List is too small for specified position (Current Size: %d)", i);
            return 1;
        }
        previous->next = p;
        p->next = tmp;
        return 0;
    }
}

int llist_remove_at(struct Person *list, int pos)
{
    struct Person *tmp = list;
    int i = 0;
    while (tmp != NULL || i < pos) {
        tmp = tmp->next;
        i++;
    }
    if (i < pos) {
        printf("List is too small for specified position (Current Size: %d)", i);
        return 1;
    }
    free(tmp);
    return 0;
}

void llist_remove_all(struct Person **list)
{
    struct Person *head = *list;
    struct Person *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
    *list = NULL;
}

struct Person *llist_find_at(struct Person *list, int pos)
{
    struct Person *tmp = NULL;
    int i = 0;
    while (tmp != NULL || i < pos) {
        tmp = tmp->next;
        i++;
    }
    if (i < pos) {
        printf("List is too small for specified position (Current Size: %d)", i);
        return NULL;
    }
    return tmp;
}

struct Person *llist_find_by(struct Person *list, char *s)
{
    struct Person *tmp = NULL;
    int i = 0;
    while (tmp != NULL) {
        tmp = list;
        if (strcmp(tmp->name, s) || strcmp(tmp->surname, s) || strcmp(tmp->email, s) || strcmp(tmp->phone, s) == 0) {
            break;
        }
        i++;
    }
    return tmp;
}