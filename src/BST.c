
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
        (*b)->occurrences = occurrencies;
        (*b)->left = NULL;
        (*b)->right = NULL;
    }else if (occurrencies < (*b)->occurrences){
        insertSBT(&(*b)->left, word, occurrencies);
    }else{
        insertSBT(&(*b)->right, word, occurrencies);
    }
}

void displayBST(BST **b){
    if(*b != NULL){
        displayBST(&(*b)->left);
        printf("%s %i\n", (*b)->word, (*b)->occurrences);
        displayBST(&(*b)->right);
    }
}

int countBstElements(BST **b){
    int num = 0;
    if(*b != NULL){
        num += countBstElements(&(*b)->left);
        num++;
        num += countBstElements(&(*b)->right);
    }

    return num;
}