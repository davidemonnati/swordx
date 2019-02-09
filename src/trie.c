
#include "trie.h"

#define ALPHABET_SIZE 26

typedef struct Trie{
    char *value;
    int occurrencies;
    struct Trie *children[ALPHABET_SIZE];
}Trie;

void _displayTrie(Trie* root, char *word, int level);

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

void trieAdd(Trie *root, char *word){
    Trie *t = createTrie();
    t = root;
    
    for(int i=0; i<strlen(word); i++){
        int index = word[i] - 'a'; // posizione lettera nell'alfabero -1 perchè l'indice parte da 0
        if(!t->children[index])
            t->children[index] = createTrie();
        
        t->children[index]-> value = &word[i];
        t = t->children[index];
    }

    t->occurrencies++;
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

void displayTrie(Trie* root, char *word){
    _displayTrie(root, word, 0);
}

void _displayTrie(Trie* root, char *word, int level){
    int i=0;
    if (root->occurrencies>0){ 
        word[level] = '\0'; 
        printf("%s\n", word);
    } 
  
    for (i = 0; i < ALPHABET_SIZE; i++){ 
        if (root->children[i]){ 
            word[level] = i + 'a'; 
            _displayTrie(root->children[i], word, level + 1); 
        } 
    } 
}
