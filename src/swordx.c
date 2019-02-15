
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <getopt.h>
#include <dirent.h>

#include "utils.h"
#include "trie.h"
#include "BST.h"
#include "stack.h"

#define FLAG_RECURSIVE (1<<0)
#define FLAG_FOLLOW (1<<1)
#define FLAG_EXCLUDE (1<<2)
#define FLAG_ALPHA (1<<3)
#define FLAG_MIN (1<<4)
#define FLAG_IGNORE (1<<5)
#define FLAG_SBO (1<<6)
#define FLAG_OUTPUT (1<<7)

int cycleDir(char *path, Trie *root, unsigned char flags, Stack *excludeFiles);
void sortTrie(BST **b, Trie* root);
void _sortTrie(BST **b, Trie* root, char *word, int level);
int main(int argc, char **argv);
void usage(char *programname);
void help(char *programname);

static struct option const long_opts[] =
        {
                {"help",             no_argument,       NULL, 'h'}, // help
                {"recursive",        no_argument,       NULL, 'r'}, // OK
                {"follow",           no_argument,       NULL, 'f'}, // link
                {"exclude",          required_argument, NULL, 'e'}, // OK
                {"alpha",            no_argument,       NULL, 'a'},
                {"min",              required_argument, NULL, 'm'}, // vengono considerate solo parole con una lunghezza minima
                {"ignore",           required_argument, NULL, 'i'}, // elenco di parole da ignorare
                {"sortbyoccurrency", no_argument,       NULL, 's'}, // OK
                {"sbo",              no_argument,       NULL, 's'}, // OK
                {"output",           required_argument, NULL, 'o'}, // OK
                {"log",              required_argument, NULL, 'l'},
                {"update",           required_argument, NULL, 'u'},
                {NULL, 0,                               NULL, 0} // required
        };

int cycleDir(char *path, Trie *root, unsigned char flags, Stack *excludeFiles){
    DIR *dir;
    dir = opendir(path);
    struct dirent *entry;
    char *absolute_path = (char*)malloc(sizeof(char));

    if(!dir){
        fprintf(stderr, "swordx: %s, %s\n", path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    while((entry=readdir(dir)) != NULL){
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..") && !searchStackElement(excludeFiles, entry->d_name)){
            sprintf(absolute_path, "%s/%s", path, entry->d_name);
            getWordsToTrie(root, absolute_path);
            if(isDir(absolute_path) && flagIsActive(FLAG_RECURSIVE, flags)) cycleDir(absolute_path, root, flags, excludeFiles);
        }
    }
    closedir(dir);

    free(absolute_path);
    return 1;
}

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
    Stack *excludeFiles = initializeNode();

    while ((c = getopt_long(argc, argv, "hrfeamisolu", long_opts, NULL)) != -1) {
        switch (c) {
            case 'h':
                help(argv[0]);
                exit(EXIT_SUCCESS);
                
            case 'r':
                flags |= FLAG_RECURSIVE;
                break;

            case 'f':
                // do something
                break;
                
            case 'e':
                flags |= FLAG_EXCLUDE;
                for (; optind < argc && *argv[optind] != '-'; optind++)
                    push(excludeFiles, argv[optind]);
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
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    
    while(argc > 1){
        if(isFile(argv[argc-1])){
            char *path = argv[argc-1];
            getWordsToTrie(t, path);
        } else if(isDir(argv[argc-1])){
            cycleDir(argv[argc-1], t, flags, excludeFiles);
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
 
void usage(char *programname){
    printf("Usage: %s [options] [inputs]\n", programname);
    printf("Try %s --help for more information.\n", programname);
}

void help(char *programname) {
    printf("Usage: %s [options] [inputs]\n", programname);
    printf("swordx count the occurrencies of each words in a file or a range of files and print them into a new file.\n\n");
    printf("\t -h,  --help\t\tshow this message\n");
    printf("\t -r,  --recursive\tcollects words from all subdirectories recursively\n");
    printf("\t -f,  --follow\t\tfollow links\n");
    printf("\t -e, <file>\n");
    printf("\t     --exclude <file>\texclude files from elaboration\n");
    printf("\t -a,  --alpha\t\tconsider only alphabetic letters\n");
    printf("\t -m, <min>\n");
    printf("\t     --min <min>\tconsider words with greater or equal length <min>\n");
    printf("\t -i, <file>\n");
    printf("\t     --ignore <file>\tall words contained in <file> will be ignored\n");
    printf("\t -s,\n");
    printf("\t     --sbo\t\tsort words by occurrences\n");
    printf("\t     --sortbyoccurrency\tsort words by occurrences\n");
    printf("\t -o, <filename>\n");
    printf("\t     --output <filename>\twrite statistics in a specific output file <filename>\n");
    printf("\t -l, <file>,  --log <file>\tgenerates log file <file> where it is reported for each file\n");
    printf("\t\t\t\t\ta line of format: '<name> cw iw time':\n");
    printf("\t\t-<name>: name file\n");
    printf("\t\t-cw: number of registered words\n");
    printf("\t\t-iw: number of ignored words\n");
    printf("\t\t-time: processing time\n");
}
