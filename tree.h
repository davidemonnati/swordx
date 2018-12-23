//
// Created by davide on 10/12/18.
//

typedef struct Tree {
    char value[100];
    int occurrences;
    struct Tree *left;
    struct Tree *right;
} Tree;

