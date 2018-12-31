//
// Created by davide on 10/12/18.
//

typedef struct Tree {
    char value[100];
    int occurrences;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree *nodeAlloc();
Tree *insertNode(Tree* albero, char *word);
Tree *getWords(Tree* albero, char *path);
char *toLowerCase(char *word);
void printTree(Tree* albero);