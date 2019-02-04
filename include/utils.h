#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <memory.h>
#include <malloc.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>

#include "tree.h"
#include "stack.h"

FILE *openFileReadMode(char *path);
FILE *openFileWriteMode(char *path);
void writeFile(FILE *file, char *value);
int flagIsActive(unsigned char option, unsigned char flags);
void printFlagsValue(unsigned char option);
unsigned char enableFlag(unsigned char flags, unsigned char option);
int isFile(char *path);
int isDir(char *path);
int cycleDir(char *path, Tree *albero);

