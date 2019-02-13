
#ifndef TREE_MODULE_TRIE_H
#define TREE_MODULE_TRIE_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "utils.h"

#define ALPHABET_SIZE 26

typedef struct Trie{
    char *value;
    int occurrencies;
    struct Trie *children[ALPHABET_SIZE];
}Trie;
 
Trie *createTrie();
void trieAdd(Trie *root, char *word);
int searchTrie(Trie *root, char *key);
void displayTrie(Trie* root);
void getWordsToTrie(Trie *root, char *path);
void writeTrie(Trie *root, char *output);

#endif