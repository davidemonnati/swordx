//
// Created by davide on 23/12/18.
//


typedef struct Stack{
    char *value;
    struct Stack *next;
} Stack;

Stack *stackNodeAlloc();
Stack *initializeNode();
Stack *push(Stack *head, char *word);
void printStack(Stack *head);
