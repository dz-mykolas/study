#include "llist.h"
#include "task_util.h"

void load_file(FILE *file, struct Person **list);
void print_possible();
int ask_num();
void do_task(struct Person **list, int task);

int main(void)
{
    char *file_name = "/addresses.csv";
    char *file_path = malloc(strlen(getenv("HOME")) + strlen(file_name) + 1);
    strcpy(file_path, getenv("HOME"));
    strcat(file_path, file_name);
    
    struct Person *list = NULL;
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
    free(file_path);
    return 0;
}