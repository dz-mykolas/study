struct Person {
    char name[30];
    char surname[30];
    char email[30];
    char phone[30];
    struct Person *next;
};