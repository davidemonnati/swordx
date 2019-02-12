
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <getopt.h>

#include "utils.h"
#include "trie.h"
#include "BST.h"

#define FLAG_RECURSIVE (1<<0)
#define FLAG_FOLLOW (1<<1)
#define FLAG_EXCLUDE (1<<2)
#define FLAG_ALPHA (1<<3)
#define FLAG_MIN (1<<4)
#define FLAG_IGNORE (1<<5)
#define FLAG_SBO (1<<6)
#define FLAG_OUTPUT (1<<7)

void sortTrie(BST **b, Trie* root);
void _sortTrie(BST **b, Trie* root, char *word, int level);
int main(int argc, char **argv);
void usage();
void printHelp();

static struct option const long_opts[] =
        {
                {"help",             no_argument,       NULL, 'h'},
                {"recursive",        no_argument,       NULL, 'r'},
                {"follow",           no_argument,       NULL, 'f'},
                {"exclude",          required_argument, NULL, 'e'},
                {"alpha",            no_argument,       NULL, 'a'},
                {"min",              required_argument, NULL, 'm'},
                {"ignore",           required_argument, NULL, 'i'},
                {"sortbyoccurrency", no_argument,       NULL, 's'},
                {"sbo",              no_argument,       NULL, 's'},
                {"output",           required_argument, NULL, 'o'},
                {"log",              required_argument, NULL, 'l'},
                {"update",           required_argument, NULL, 'u'},
                {NULL, 0,                               NULL, 0} // required
        };

void sortTrie(BST **b, Trie* root){
    char *word = (char*)malloc(sizeof(char));
    _sortTrie(b, root, word, 0);
}

void _sortTrie(BST **b, Trie* root, char *word, int level){
    int i=0;
    if (root->occurrencies>0){ 
        word[level] = '\0';
        insertSBT(b, word, root->occurrencies);
    } 
  
    for (i = 0; i < ALPHABET_SIZE; i++){ 
        if (root->children[i]){ 
            word[level] = i + 'a'; 
            _sortTrie(b, root->children[i], word, level + 1);
        } 
    }
}

int main(int argc, char **argv) {
    int c;
    char *output = NULL;
    unsigned char flags = 0;
    Trie *t = createTrie();
    BST **sbo = createBST(); 

    while ((c = getopt_long(argc, argv, "hrfeamisolu", long_opts, NULL)) != -1) {
        switch (c) {
            case 'h':
                printHelp();
                exit(EXIT_SUCCESS);
                
            case 'r':
                // do something
                break;

            case 'f':
                // do something
                break;
                
            case 'e':
                // do something
                break;

            case  'a':
                // do something
                break;
            
            case 'm':
                // do something
                break;

            case 'i':
                // do something
                break;

            case 's':
                flags |= FLAG_SBO; 
                break;

            case 'o':
                output=(char*)malloc(sizeof(char));
                output = optarg;
            	break;

            case 'l':
                // do something
                break;

            case 'u':
                // do something
                break;
        }
    }

    if(argc < 2){
        fprintf(stderr, "swordx: no input files or directory\n");
        usage();
        exit(EXIT_FAILURE);
    }
    
    while(argc > 1){
        if(isFile(argv[argc-1])){
            char *path = argv[argc-1];
            getWordsToTrie(t, path);
        } else if(isDir(argv[argc-1])){
            cycleDir(argv[argc-1], t);
        }
        argc--;
    }

    // controllo se c'è SBO attivo
    if(flagIsActive(FLAG_SBO, flags)){
        sortTrie(sbo, t);
        printBST(sbo, output);
    }else writeTrie(t, output);
    
    free(t);
    free(sbo);
    return 0;
}

void usage(){
    printf("Usage: swordx [options] [inputs]\n");
}

void printHelp() {
    printf("Uso: swordx [options] [inputs]\n");
    printf("SWORDX: Stampo help qui\n");
}
