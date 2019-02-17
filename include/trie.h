
#ifndef TREE_MODULE_TRIE_H
#define TREE_MODULE_TRIE_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

#define ALPHABET_SIZE 36

typedef struct Trie{
    char value;
    int occurrencies;
    struct Trie *children[ALPHABET_SIZE];
}Trie;
 
Trie *createTrie();
void trieAdd(Trie *root, char *word);
int searchTrie(Trie *root, char *key);
void displayTrie(Trie* root);
int countTrieElements(Trie *root);

#endif