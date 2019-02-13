#ifndef TREE_MODULE_BST_H
#define TREE_MODULE_BST_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "utils.h"

typedef struct BST {
    char *word;
    int occurrencies;
    struct BST *left;
    struct BST *right;
} BST;

BST **createBST();
void insertSBT(BST **b, char* word, int occurrencies);
void displayBST(BST **b);
void printBST(BST **b, char *output);

#endif