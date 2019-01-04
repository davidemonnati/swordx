#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "../include/stack.h"

typedef struct Stack{
    char *value;
    struct Stack *next;
} Stack;


Stack *initializeNode(){
    Stack* head = (Stack *) malloc(sizeof(Stack));
    head->value = NULL; // = (char *) malloc((wordLength+1)*sizeof(char));
    head->next = NULL;
    return head;
}

Stack *push(Stack *stack, char *word) {
    Stack *newStack = initializeNode(strlen(word));
    newStack->value = (char *) malloc((strlen(word)+1) * sizeof(char));
    strcpy(newStack->value, word);
    newStack->next = stack;
    return newStack;
}

void pop(Stack *head){
    if(head->value == NULL){
        perror("SWORDX: Impossibile effettuare il pop, lo stack è vuoto");
        exit(EXIT_FAILURE);
    }

    Stack *tmp = (Stack *) malloc(sizeof(Stack*));
    printf("%s\n", head->value);
    *tmp = *head->next;
    *head = *tmp;
    free(tmp);
}

void printStack(Stack *head) {
    if(head->value ==  NULL) return;
    printf("%s\n", head->value);
    return printStack(head->next);
}

char *getStackValue(Stack *head){
    return head->value;
}

Stack *getNextStackElement(Stack *head){
    return head->next;
}

int searchStackElement(Stack *head, char *value){
    int i = 0;
    while(head != NULL){
        if(strcmp(head->value, value)==0){
            i++;
            return i;
        }
        else{
            head = head->next;
        }
    }

    return i;
}
