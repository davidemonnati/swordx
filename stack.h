//
// Created by davide on 23/12/18.
//


typedef struct Stack{
    char *value;
    struct Stack *next;
} Stack;

Stack *listNodeAlloc();
Stack *initializeList();
Stack *listAddElement(Stack *head, char *word);
