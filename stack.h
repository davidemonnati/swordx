//
// Created by davide on 23/12/18.
//


typedef struct Stack{
    char *value;
    struct Stack *next;
} Stack;

Stack *stackNodeAlloc();
Stack *initializeStack();
Stack *stackAddElement(Stack *head, char *word);
