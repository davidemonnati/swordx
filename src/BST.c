
#include "BST.h"

typedef struct BST {
    struct Trie *node;
    struct BST *left;
    struct BST *right;
} BST;

BST *createBST(){
    return (BST*)malloc(sizeof(BST));
}
