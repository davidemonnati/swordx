#ifndef TREE_MODULE_BST_H
#define TREE_MODULE_BST_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct BST {
    char *word;
    int occurrences;
    struct BST *left;
    struct BST *right;
} BST;

BST **createBST();
void insertSBT(BST **b, char* word, int occurrencies);
void displayBST(BST **b);
int countBstElements(BST **b);

#endif