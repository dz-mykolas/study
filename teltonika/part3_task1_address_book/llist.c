#include <stdio.h>
#include <stdlib.h>

#include "llist.h"

struct Person *createNode(char *name, char *surname, char *email, char *phone)
{
    
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
}

int llist_add_at(struct Person **list, struct Person *p, int pos)
{
    // check head
    struct Person *tmp = *list;
    if (tmp == NULL){
        if (pos != 0)
            return 1;
        *list = p;
        return 0;
    }

    int i = 0;
    while (tmp->next != NULL && i < pos){
        previous = tmp;
        tmp = tmp->next;
        i++;
    }
    if (pos > i)
        return 1;
    previous->next = p;
    p->next = tmp;
}