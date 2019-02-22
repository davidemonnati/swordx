
#include "trie.h"

int getIndex(char c);
void _displayTrie(Trie* root, char *word, int level);

Trie *createTrie(){
    Trie *t = (Trie*)malloc(sizeof(Trie));
    t->occurrencies = 0;
    int i=0;

    for(i=0; i<ALPHABET_SIZE; i++){
        t->children[i] = NULL;
    }

    return t;
}

int getIndex(char c){
    if(isdigit(c))
        return c - '0';
    else
        return c - 'a' + 10;
}

void trieAdd(Trie *root, char *word){
    Trie *t = createTrie();
    t = root;
    
    for(int i=0; i<strlen(word); i++){
        int index = getIndex(word[i]);

        if(!t->children[index])
            t->children[index] = createTrie();
        
        t->children[index]->value = word[i];
        t = t->children[index];
    }

    t->occurrencies++;
}

int searchTrie(Trie *root, char *key){
    if(root == NULL)
        return 0;
    
    Trie *tNode = root;
  
    for(int i=0; i<strlen(key); i++){
        int index =  getIndex(key[i]);
        
        if(!tNode->children[index])
            return 0;
  
        tNode = tNode->children[index];

        if(tNode->occurrencies > 0) // parola trovata
            return 1;
    }
  
    return 0; 
}

void displayTrie(Trie* root){
    char *word = (char*)malloc(sizeof(char));
    _displayTrie(root, word, 0);
    free(word);
}

void _displayTrie(Trie* root, char *word, int level){
    int i=0;
    if (root->occurrencies>0){ 
        word[level] = '\0'; 
        printf("%s: %i\n", word, root->occurrencies);
    } 
  
    for (i = 0; i < ALPHABET_SIZE; i++){ 
        if (root->children[i]){ 
            word[level] = root->children[i]->value;
            _displayTrie(root->children[i], word, level + 1); 
        } 
    } 
}

int countTrieElements(Trie *root){
    int num = 0;
    if(root == NULL) return 0;
    if(root->occurrencies > 0)
        num++;
    
    for (int i = 0; i < ALPHABET_SIZE; i++){ 
        if (root->children[i])
            num += countTrieElements(root->children[i]);
    }

    return num;
}