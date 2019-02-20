
#include "utils.h"

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

int isLink(char *path){
    struct stat statbuf;
    if(lstat(path, &statbuf)) return 0;
    if(S_ISLNK(statbuf.st_mode)) return 1;

    return 0;
}

char *toLowerCase(char *word){
    int i = 0;
    for (i=0; i < strlen(word) + 1; i++) word[i] = tolower(word[i]);
    return word;
}

void errorman(char *error_desc){
	perror(error_desc);
	exit(EXIT_FAILURE);
}
