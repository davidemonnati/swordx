
#ifndef TREE_MODULE_OPTMAN_H
#define TREE_MODULE_OPTMAN_H

#include <getopt.h>

#define FLAG_RECURSIVE (1<<0)
#define FLAG_FOLLOW (1<<1)
#define FLAG_EXCLUDE (1<<2)
#define FLAG_ALPHA (1<<3)
#define FLAG_MIN (1<<4)
#define FLAG_IGNORE (1<<5)
#define FLAG_SBO (1<<6)
#define FLAG_OUTPUT (1<<7)

int flagStatus(unsigned char option, unsigned char flags);
void printFlagsValue(unsigned char option);
unsigned char enableFlag(unsigned char flags, unsigned char option);
static struct option const long_opts[];


#endif
