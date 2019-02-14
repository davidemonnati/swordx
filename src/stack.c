
#include "stack.h"

typedef struct Stack{
    char *value;
    struct Stack *next;
} Stack;


Stack *initializeNode(){
    Stack* head = (Stack *) malloc(sizeof(Stack));
    head->value = NULL;
    head->next = NULL;
    return head;
}

void *push(Stack *stack, char *word) {
    Stack *newStack = initializeNode();
    newStack->value = (char *) malloc((strlen(word)+1) * sizeof(char));
    strcpy(newStack->value, word);
    newStack->next = initializeNode();
    *newStack->next = *stack;
    *stack = *newStack;
    free(newStack);
    return stack;
}

char *pop(Stack *head){
    char *headValue = head->value;
    if(head->value == NULL){
        // perror("SWORDX: Error, stack is empty.");
        // exit(EXIT_FAILURE);
    }
    Stack *tmp = initializeNode();
    *tmp = *head->next;
    *head = *tmp;
    free(tmp);
    return headValue;
}

void printStack(Stack *head) {
    if(head->value ==  NULL) return;
    printf("%s\n", head->value);
    return printStack(head->next);
}

char *getTopStack(Stack *head){
    return head->value;
}

int searchStackElement(Stack *head, char *value) {
    int i = 0;
    while (head->value != NULL) {
        if (strcmp(head->value, value) == 0) {
            i++;
            return i;
        } else {
            head = head->next;
        }
    }

    return i;
}

int stackIsEmpty(Stack *head){
    if(head->value == NULL) return 1;
    return 0;
}
