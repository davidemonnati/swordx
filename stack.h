//
// Created by davide on 23/12/18.
//


typedef struct Stack{
    char *value;
    struct Stack *next;
} Stack;

Stack *initializeNode(int wordLength);
Stack *push(Stack *stack, char *word);
void pop(Stack *head);
void printStack(Stack *head);
char *getStackValue(Stack *head);
Stack *getNextStackElement(Stack *head);
int searchStackElement(Stack *head, char *value);