
#ifndef SWORDX_MODULE_UTILS_H
#define SWORDX_MODULE_UTILS_H

// #include <stdio.h>
// #include <getopt.h>
// #include <memory.h>
// #include <malloc.h>
// #include <errno.h>
// #include <dirent.h>

#include "tree.h"
#include "stack.h"

/* Defining flags */

#define FLAG_RECURSIVE (1<<0)
#define FLAG_FOLLOW (1<<1)
#define FLAG_EXCLUDE (1<<2)
#define FLAG_ALPHA (1<<3)
#define FLAG_MIN (1<<4)
#define FLAG_IGNORE (1<<5)
#define FLAG_SBO (1<<6)
#define FLAG_OUTPUT (1<<7)


FILE *openFileReadMode(char *path);
FILE *openFileWriteMode(char *path);
void writeFile(FILE *file, char *value);
int flagStatus(unsigned char option, unsigned char flags);
void printFlagsValue(unsigned char option);
unsigned char enableFlag(unsigned char flags, unsigned char option);
int typeFile(char *path);
int typeDir(char *path);
int cycleDir(char *path, Tree *albero);

#endif //SWORDX_MODULE_UTILS_H
