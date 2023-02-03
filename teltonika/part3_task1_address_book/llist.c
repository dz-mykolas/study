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
    struct Person *temp = list;
    int i = 0;
    while (temp != NULL) {
        temp = temp->next;
        i++;
    }
    return i;
}

void person_print(struct Person *p)
{
    printf("%s %s %s %s\n", p->name, p->surname, p->email, p->phone);
}

void llist_print(struct Person *list)
{
    struct Person *temp = list;
    while (temp != NULL) {
        person_print(temp);
        temp = temp->next;
    }
}

void llist_add_end(struct Person **list, struct Person *p)
{
    // check head
    struct Person *temp = *list;
    if (temp == NULL) {
        *list = p;
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = p;
}

int llist_add_at(struct Person **list, struct Person *p, int pos)
{
    struct Person *temp = *list;
    if (pos == 0) {
        if (temp == NULL) {
            *list = p;
        } else {
            p->next = *list;
            *list = p;
        }
        return 0;
    }

    if (temp == NULL) {
        printf("List has 0 elements, can not assign to position %d", pos);
        return 1;
    } else {
        struct Person *previous;
        int i = 0;
        while (temp != NULL && i < pos) {
            previous = temp;
            temp = temp->next;
            i++;
        }
        if (i < pos) {
            printf("List is too small for specified position (Current Size: %d)", i);
            return 1;
        }
        previous->next = p;
        p->next = temp;
        return 0;
    }
}

void llist_remove_at(struct Person **list, int pos)
{
    struct Person *current = *list;
    if (current == NULL) {
        printf("List has 0 elements");
        return;
    }
    if (pos == 0) {
        *list = current->next;
        free(current);
        return;
    }

    int i = 0;
    while (current != NULL && i + 1 < pos) {
        current = current->next;
        i++;
    }
    if (current == NULL || current->next == NULL) {
        printf("List is too small for specified position\n");
        return;
    }
    struct Person *temp = current->next->next;
    free(current->next);
    current->next = temp;
}

void llist_remove_all(struct Person **list)
{
    struct Person *head = *list;
    struct Person *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    *list = NULL;
}

struct Person *llist_find_at(struct Person *list, int pos)
{
    struct Person *temp = NULL;
    int i = 0;
    while (temp != NULL || i < pos) {
        temp = temp->next;
        i++;
    }
    if (i < pos) {
        printf("List is too small for specified position (Current Size: %d)", i);
        return NULL;
    }
    return temp;
}

struct Person *llist_find_by(struct Person *list, char *s)
{
    struct Person *temp = NULL;
    int i = 0;
    while (temp != NULL) {
        temp = list;
        if (strcmp(temp->name, s) || strcmp(temp->surname, s) || strcmp(temp->email, s) || strcmp(temp->phone, s) == 0) {
            break;
        }
        i++;
    }
    return temp;
}