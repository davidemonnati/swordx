//
// Created by davide on 29/12/18.
//

#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include "../include/managefile.h"

FILE *openFileReadMode(char *path){
    FILE *rf = fopen(path, "r");
    if(rf == NULL) fprintf(stderr, "SWORDX: Error opening file. \n");
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
