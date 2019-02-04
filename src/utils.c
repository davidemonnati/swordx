
#include "utils.h"


/* File management functions */

FILE *openFileReadMode(char *path){
    FILE *rf = fopen(path, "r");
    if(!rf){
        fprintf(stderr, "swordx: %s, %s\n", path, strerror(errno));
        exit(EXIT_FAILURE);
    }
    return rf;
}

FILE *openFileWriteMode(char *path){
    FILE *wf = fopen(path, "a");
    return wf;
}

void writeFile(FILE *file, char *value){
    fputs(value, file);
    fclose(file);
}

/* Option and flag management functions */

int flagIsActive(unsigned char option, unsigned char flags){
    if(flags & option) return 1;
    else return 0;

    return 0;
}

void printFlagsValue(unsigned char option){
    printf("%u\n", option);
}

unsigned char enableFlag(unsigned char flags, unsigned char option){
    flags |= option;
    return flags;
}

/* Dir and file management functions */

int isFile(char *path){
    struct stat statbuf;
    if(lstat(path, &statbuf)) return 0; // il file o cartella non esiste
    if(S_ISREG(statbuf.st_mode)) return 1;

    return 0;
}

int isDir(char *path){
    struct stat statbuf;
    if(lstat(path, &statbuf)) return 0; // il file o cartella non esiste
    if(S_ISDIR(statbuf.st_mode)) return 1;

    return 0;
}

int cycleDir(char *path, Tree *albero){
    DIR *dir;
    dir = opendir(path);
    char *complete_path = (char*)malloc(sizeof(char));

    if(!dir){
        fprintf(stderr, "swordx: %s, %s\n", path, strerror(errno));
        exit(EXIT_FAILURE);
    }

    while(dir){
        struct dirent *entry;
        char *file_name;

        entry = readdir(dir);
        if(!entry) break;
        file_name = entry->d_name;
        if(!strcmp(file_name, ".") ||!strcmp(file_name, "..")) continue; // non considera le cartelle .. e .
        sprintf(complete_path, "%s/%s", path, file_name);

        // getWords(albero, complete_path); // DA DECOMMENTARE
    }
    closedir(dir);

    free(complete_path);
    return 1;
}
