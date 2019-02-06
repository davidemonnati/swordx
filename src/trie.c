
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

void trieAdd(Trie *root, char* word){    
    struct Trie *addTrie = root;
    int i=0;
    for(i=0; i< strlen(word); i++){
        int index = word[i] - 'a'; // posizione lettera nell'alfabero -1 perchè l'indice parte da 0
        if(!addTrie->children[index])
            addTrie->children[index] = createTrie();

        addTrie = addTrie->children[index];
    }

    addTrie->occurrencies++;
}

