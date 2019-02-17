#ifndef TREE_MODULE_UTILS_H
#define TREE_MODULE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <memory.h>
#include <malloc.h>
#include <errno.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"

int flagIsActive(unsigned char option, unsigned char flags);
void printFlagsValue(unsigned char option);
unsigned char enableFlag(unsigned char flags, unsigned char option);
int isFile(char *path);
int isDir(char *path);
int isLink(char *path);
char *toLowerCase(char *word);

#endif