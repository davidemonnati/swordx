#ifndef TREE_MODULE_BST_H
#define TREE_MODULE_BST_H

#include <stdio.h>
#include <malloc.h>

typedef struct BST {
    struct Trie *node;
    struct BST *left;
    struct BST *right;
} BST;

BST *createBST();

#endif