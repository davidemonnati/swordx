//
// Created by davide on 23/12/18.
//


typedef struct Stack{
    char *value;
    struct Stack *next;
} Stack;

Stack *stackNodeAlloc();
Stack *initializeNode();
Stack *push(Stack *stack, char *word);
void printStack(Stack *head);
void pop(Stack *head);