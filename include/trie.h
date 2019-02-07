
#ifndef TREE_MODULE_TRIE_H
#define TREE_MODULE_TRIE_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct Trie Trie;

Trie *initializeTrie();
Trie *createTrie();
int searchTrie(Trie *root, char *key);
void displayTrie(Trie* root);

#endif