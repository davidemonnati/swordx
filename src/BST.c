
#include "BST.h"

BST **createBST(){
    BST **b = (BST**)malloc(sizeof(BST*));
    return b;
}

void insertSBT(BST **b, char* word, int occurrencies){
    if(*b == NULL){
        char *tmp = (char*)malloc(sizeof(char));
        strcpy(tmp, word);
        (*b) = (BST*)malloc(sizeof(BST));
        (*b)->word = tmp;
        (*b)->occurrencies = occurrencies;
        (*b)->left = NULL;
        (*b)->right = NULL;
    }else if (occurrencies < (*b)->occurrencies){
        insertSBT(&(*b)->left, word, occurrencies);
    }else{
        insertSBT(&(*b)->right, word, occurrencies);
    }
}

void displayBST(BST **b){
    if(*b != NULL){
        displayBST(&(*b)->left);
        printf("%s %i\n", (*b)->word, (*b)->occurrencies);
        displayBST(&(*b)->right);
    }
}

void printBST(BST **b, char *output){
    if(*b != NULL){
        printBST(&(*b)->left, output);
        char *str = (char *) malloc(sizeof(char));
        sprintf(str, "%s %i\n", (*b)->word, (*b)->occurrencies);
        (output == NULL) ? output = "swordx.out" : NULL;
        writeFile(openFileWriteMode(output), str);
        printBST(&(*b)->right, output);
    }
}