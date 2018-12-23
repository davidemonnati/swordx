//
// Created by davide on 23/12/18.
//


typedef struct List{
    char *value;
    struct List *next;
} List;

List *listNodeAlloc();
List *initializeList();
List *listAddElement(List *head, char *word);
