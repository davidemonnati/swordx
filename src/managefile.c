//
// Created by davide on 29/12/18.
//

#include "../include/managefile.h"

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
