#ifndef TREE_MODULE_TREE_H
#define TREE_MODULE_TREE_H

#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include "managefile.h"

typedef struct Tree Tree;

Tree *nodeAlloc();
Tree *insertNode(Tree* albero, char *word);
Tree *getWords(Tree* albero, char *path);
char *toLowerCase(char *word);
void printTree(Tree* albero);
void printfTree(Tree* albero);

#endif //TREE_MODULE_TREE_H
