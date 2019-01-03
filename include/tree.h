//
// Created by davide on 10/12/18.
//

typedef struct Tree Tree;

Tree *nodeAlloc();
Tree *insertNode(Tree* albero, char *word);
Tree *getWords(Tree* albero, char *path);
char *toLowerCase(char *word);
void printTree(Tree* albero);