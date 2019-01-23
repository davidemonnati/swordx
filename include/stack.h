

#ifndef TREE_MODULE_STACK_H
#define TREE_MODULE_STACK_H

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Stack Stack;

Stack *initializeNode();
void *push(Stack *stack, char *word);
void pop(Stack *head);
void printStack(Stack *head);
char *getStackValue(Stack *head);
Stack *getNextStackElement(Stack *head);
int searchStackElement(Stack *head, char *value);


#endif //TREE_MODULE_STACK_H
