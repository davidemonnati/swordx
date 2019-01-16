#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include "stack.h"

FILE *openFileReadMode(char *path);
FILE *openFileWriteMode(char *path);
void writeFile(FILE *file, char *value);
void groupFiles(Stack *head, int argc, char **argv);