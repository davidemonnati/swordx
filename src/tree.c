
#include "tree.h"
#include "utils.h"

typedef struct Tree {
    char value[100];
    int occurrences;
    struct Tree *left;
    struct Tree *right;
} Tree;

Tree *nodeAlloc() {
    return (Tree *) malloc(sizeof(Tree));
}

Tree *insertNode(Tree* albero, char *word) {
    if (albero == NULL) {
        albero = nodeAlloc();
        strcpy(albero->value, word);
        albero->occurrences = 1;
        albero->left = NULL;
        albero->right = NULL;
    } else if (strcmp(word, albero->value) == 0) {
        albero->occurrences += 1;
    } else if (strcmp(word, albero->value) < 0) {
        albero->left = insertNode(albero->left, word);
    } else if (strcmp(word, albero->value) > 0) {
        albero->right = insertNode(albero->right, word);
    }
    return albero;
}

Tree *getWords(Tree* albero, char *path) {
    FILE *rFile = openFileReadMode(path);
    char *buffer, *word;
    size_t linesize = 0;

    // Stampo il contenuto del file
    while (getline(&buffer, &linesize, rFile) > 0) {
        word = strtok(buffer, " ,.:;-_[]()/!£$%&?^|*€@#§°*'\n");
        while (word != NULL) {
            albero = insertNode(albero, toLowerCase(word));
            word = strtok(NULL, " ,.:;-_[]()/!£$%&?^|*€@#§°*'\n");
        }
    }
    fclose(rFile);
    return albero;
}

char *toLowerCase(char *word) {
    int i = 0;
    for (i=0; i < strlen(word) + 1; i++) word[i] = tolower(word[i]);
    return word;
}

void printTree(Tree* albero) {
    if (albero != NULL) {
        printTree(albero->left);
        char *word = (char *) malloc(sizeof(char));
        sprintf(word, "%s %i\n", albero->value, albero->occurrences);
        writeFile(openFileWriteMode("swordx.out"), word);
        printTree(albero->right);
    }
}

void printfTree(Tree* albero) {
    if (albero != NULL) {
        printTree(albero->left);
        printf("%s %i\n", albero->value, albero->occurrences);
        printTree(albero->right);
    }
}
