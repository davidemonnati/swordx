
#ifndef TREE_MODULE_TRIE_H
#define TREE_MODULE_TRIE_H

#include <stdio.h>
#include <string.h>
#include <malloc.h>

#include "utils.h"

typedef struct Trie Trie;
 
Trie *createTrie();
void trieAdd(Trie *root, char *word);
int searchTrie(Trie *root, char *key);
void displayTrie(Trie* root);
void getWordsToTrie(Trie *root, char *path);
void writeTrie(Trie *root, char *output);
int cycleDir(char *path, Trie *root);

#endif