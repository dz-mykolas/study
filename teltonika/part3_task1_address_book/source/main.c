#include <signal.h>
#include "llist.h"
#include "task_util.h"
#include "main_helper.h"

static int running = 1;
static void sig_handler(int signum)
{
    printf("\nCTRL+C. Exiting\n");
    running = 0;
}

int main(void)
{
    struct sigaction sa;
    sa.sa_handler = sig_handler;
    sigaction(SIGINT, &sa, NULL);
    
    char *file_name = "/addresses.csv";
    char file_path[200];
    strcpy(file_path, getenv("HOME"));
    strcat(file_path, file_name);
    
    struct Person *list = NULL;
    file_open(file_path, list);

    while (running)
    {
        print_possible();
        switch (ask_num()) {
            case 1:
                running = 0;
                break;
            case 2:
                task_print(list);
                break;
            case 3:
                task_add_end(&list);
                break;
            case 4:
                task_add_at(&list);
                break;
            case 5:
                task_remove_at(list);
                break;
            case 6:
                task_remove_all(list);
                break;
            case 7:
                task_find_at(list);
                break;
            case 8:
                task_find_by(list);
                break;
            default:
                printf("Task does not exist!\n");
                break;
        }
    }
    llist_remove_all(&list);
    return 0;
}