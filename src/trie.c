
#include "trie.h"

#define ALPHABET_SIZE 36

typedef struct Trie{
    char *value;
    int occurrencies;
    struct Trie *children[ALPHABET_SIZE];
}Trie;

Trie *createTrie(){
    Trie *t = (Trie*)malloc(sizeof(Trie));
    t->value = NULL;
    t->occurrencies = 0;

    int i=0;

    for(i=0; i<ALPHABET_SIZE; i++){
        t->children[i] = NULL;
    }

    return t;
}

int searchTrie(Trie *root, char *key){
    Trie *tNode = root; 
  
    for (int i=0; i<strlen(key); i++) 
    { 
        int index = key[i] - 'a';
        if(!tNode->children[index])
            return 0;
  
        tNode = tNode->children[index]; 
    } 
  
    return 1; 
}

void displayTrie(Trie *root){
    if(root != NULL){
        if(root->occurrencies>0)
            printf("%s: %i\n", root->value, root->occurrencies);

        for(int i=0;i<ALPHABET_SIZE;i++)
            displayTrie(root->children[i]);
    }
}
