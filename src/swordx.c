
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <getopt.h>
#include <dirent.h>
#include <time.h>

#include "utils.h"
#include "trie.h"
#include "BST.h"
#include "stack.h"

#define FLAG_RECURSIVE (1<<0)
#define FLAG_FOLLOW (1<<1)
#define FLAG_EXCLUDE (1<<2)
#define FLAG_ALPHA (1<<3)
#define FLAG_SBO (1<<4)
#define FLAG_LOG (1<<5)

FILE *readFile(char *path);
FILE *writeFile(char *output);
void getIgnoredWords(Trie* ignoreTrie, char *path);
int isAlphanumeric(char *word);
int cycleDir(char *path, Trie *root, unsigned char flags, Stack *excludeFiles, int min, Trie *ignoredWords, char *logFileName);
void sortTrie(BST **b, Trie* root, char *word, int level);
void getWordsToTrie(Trie *root, char *path, unsigned char flags, int min, Trie *ignoredWords, char *logFileName);
void printBST(BST **b, FILE *pf);
void writeTrie(Trie *root, char* word, FILE *pf, int level);
void printInfo(FILE *pf, char *value, int occ);
FILE *createCSV(char *path);
int main(int argc, char **argv);
void usage(char *programName);
void help(char *programName);

static struct option const long_opts[] =
        {
                {"help",             no_argument,       NULL, 'h'}, // OK
                {"recursive",        no_argument,       NULL, 'r'}, // OK
                {"follow",           no_argument,       NULL, 'f'}, // link
                {"exclude",          required_argument, NULL, 'e'}, // OK
                {"alpha",            no_argument,       NULL, 'a'}, // OK
                {"min",              required_argument, NULL, 'm'}, // OK
                {"ignore",           required_argument, NULL, 'i'}, // OK
                {"sortbyoccurrency", no_argument,       NULL, 's'}, // OK
                {"sbo",              no_argument,       NULL, 's'}, // OK
                {"output",           required_argument, NULL, 'o'}, // OK
                {"log",              required_argument, NULL, 'l'},
                {"update",           required_argument, NULL, 'u'},
                {NULL, 0,                               NULL, 0} // required
        };

FILE *readFile(char *path){
    FILE *pf = fopen(path, "rb");
    if(pf == NULL){
        perror("Error reading file");
    }
    return pf;
}

FILE *writeFile(char *output){
    FILE *pf = fopen(output, "wb");
    if(pf == NULL){
        perror("Error writing file");
    }
    return pf;
}

void getIgnoredWords(Trie* ignoreTrie, char *path){
    FILE *rFile = readFile(path);
    char *buffer, *str;
    size_t linesize = 0;

    if(rFile == NULL) perror("Error opening file");

    while (getline(&buffer, &linesize, rFile) > 0){
        str = strtok(buffer, " .,:;\n");
        while(str != NULL){
            trieAdd(ignoreTrie, str);
            str = strtok(NULL, " .,:;\n");
        } 
    }
}

int isAlphanumeric(char *word) {
	for(int i = 0; i < strlen(word); i++)
		if(isdigit(word[i]))
            return 1;
    return 0;
}

int cycleDir(char *path, Trie *root, unsigned char flags, Stack *excludeFiles, int min, Trie *ignoredWords, char *logFileName){
    DIR *dir;
    dir = opendir(path);
    struct dirent *entry;
    char *absolute_path = (char*)malloc(sizeof(char));

    if(!dir){
        fprintf(stderr, "swordx: %s, %s\n", path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    while((entry=readdir(dir)) != NULL){
        sprintf(absolute_path, "%s/%s", path, entry->d_name);
        if(strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..") && !searchStackElement(excludeFiles, absolute_path) ){
            getWordsToTrie(root, absolute_path, flags, min, ignoredWords, logFileName);
            if(isDir(absolute_path) && flagIsActive(FLAG_RECURSIVE, flags))
                cycleDir(absolute_path, root, flags, excludeFiles, min, ignoredWords, logFileName);
        }
    }
    closedir(dir);

    free(absolute_path);
    return 1;
}

void sortTrie(BST **b, Trie* root, char *word, int level){
    int i=0;
    if (root->occurrencies>0){ 
        word[level] = '\0';
        insertSBT(b, word, root->occurrencies);
    } 
  
    for (i = 0; i < ALPHABET_SIZE; i++){ 
        if (root->children[i]){ 
            word[level] = root->children[i]->value;
            sortTrie(b, root->children[i], word, level + 1);
        } 
    }
}

void getWordsToTrie(Trie *root, char *path, unsigned char flags, int min, Trie *ignoredWords, char *logFileName){
    FILE *rFile = readFile(path);
    char *buffer, *word;
    int countWords=0, totWords=0, countIgnored=0;
    double executionTime = 0;
    size_t linesize = 0;
    clock_t start, end;

    start = clock();
    while (getline(&buffer, &linesize, rFile) > 0){
        word = strtok(buffer, " ,.:;-_[]()/!£$%&?^|*€@#§°*'\n");
        while (word != NULL) { 
            if((!flagIsActive(FLAG_ALPHA, flags) || !isAlphanumeric(word))){
                if(strlen(word) >= min && !searchTrie(ignoredWords, word)){
                    countWords++;
                    trieAdd(root, toLowerCase(word));
                }
            }
            word = strtok(NULL, " ,.:;-_[]()/!£$%&?^|*€@#§°*'\n");
        }
    }
    fclose(rFile);
    totWords = countTrieElements(root);

    end = clock();
    if(flagIsActive(FLAG_LOG, flags) && isFile(path)){
        FILE *writecsv = createCSV(logFileName);
        executionTime = (double)end-start;
        countIgnored = totWords-countWords;
        fprintf(writecsv, "%s,%i,%i,%lf\n", path, countWords, countIgnored, executionTime);
    }
}

void printBST(BST **b, FILE *pf){
    if(*b != NULL){
        printBST(&(*b)->left, pf);
        printInfo(pf, (*b)->word, (*b)->occurrences);
        printBST(&(*b)->right, pf);
    }
}

void writeTrie(Trie *root, char* word, FILE *pf, int level){
    int i=0;
    if (root->occurrencies>0){
        word[level] = '\0'; 
        printInfo(pf, word, root->occurrencies);
    } 
  
    for (i = 0; i < ALPHABET_SIZE; i++){ 
        if (root->children[i]){
            word[level] = root->children[i]->value;
            writeTrie(root->children[i], word, pf, level + 1); 
        } 
    }
}

void printInfo(FILE *pf, char *value, int occ){
    fprintf(pf, "%s: %i\n", value, occ);
}

FILE *createCSV(char *path){
    char *fileName = (char*)malloc(sizeof(char));
    sprintf(fileName, "%s.csv", path);
    FILE *pf;
    if((fopen(fileName, "rb")) == NULL){
        pf = fopen(fileName, "wb");
        fprintf(pf, "name,cw,iw,time\n");
        return pf;
    }
    pf = fopen(fileName, "a");
    return pf;
}

int main(int argc, char **argv) {
    int c, min=0, nparams=0;
    char *output = NULL;
    char *logFileName = (char*)malloc(sizeof(char));
    unsigned char flags = 0;
    Trie *t = createTrie();
    Trie *ignoredWords = createTrie();
    BST **sbo = createBST(); 
    Stack *excludeFiles = initializeNode();
    FILE *wFile;

    while ((c = getopt_long(argc, argv, "hrfeamisolu", long_opts, NULL)) != -1) {
        switch (c) {
            case 'h':
                help(argv[0]);
                exit(EXIT_SUCCESS);
                
            case 'r':
                flags |= FLAG_RECURSIVE;
                break;

            case 'f':
                flags |= FLAG_FOLLOW;
                break;
                
            case 'e':
                flags |= FLAG_EXCLUDE;
                push(excludeFiles, optarg);
                break;

            case 'a':
                flags |= FLAG_ALPHA;
                break;
            
            case 'm':
                min = atoi(optarg);
                break;

            case 'i':
                getIgnoredWords(ignoredWords, optarg);
                break;

            case 's':
                flags |= FLAG_SBO; 
                break;

            case 'o':
                output=(char*)malloc(sizeof(char));
                output = optarg;
            	break;

            case 'l':
                flags |= FLAG_LOG;
                logFileName = optarg;
                break;

            case 'u':
                // do something
                break;
        }
    }

    (output == NULL) ? output = "swordx.out" : NULL; // di default il file di output si chiama swordx.out
    wFile = writeFile(output);
    
    nparams = argc-optind; // number of files and folders

    if(argc < 2){
        fprintf(stderr, "swordx: no input files or directory\n");
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    
    for(int i = 0; i<nparams; i++){
        if(isFile(argv[argc-1])){
            char *path = argv[argc-1];
            getWordsToTrie(t, path, flags, min, ignoredWords, logFileName);
        } else if(isDir(argv[argc-1])){
            cycleDir(argv[argc-1], t, flags, excludeFiles, min, ignoredWords, logFileName);
        }
    }

    char *word = (char*) malloc(sizeof(word));

    // controllo se c'è SBO attivo
    if(flagIsActive(FLAG_SBO, flags)){
        sortTrie(sbo, t, word, 0);
        printBST(sbo, wFile);
    }else{
        writeTrie(t, word, wFile, 0);
    }

    fclose(wFile);
    free(word);
    free(t);
    free(ignoredWords);
    free(sbo);

    return 0;
}
 
void usage(char *programName){
    printf("Usage: %s [options] [inputs]\n", programName);
    printf("Try %s --help for more information.\n", programName);
}

void help(char *programName) {
    printf("Usage: %s [options] [inputs]\n", programName);
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
