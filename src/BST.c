
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

void printBST(BST **b){
    if(*b != NULL){
        printBST(&(*b)->left);
        printf("%s %i\n", (*b)->word, (*b)->occurrencies);
        printBST(&(*b)->right);
    }
}
