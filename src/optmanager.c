
#include <stdio.h>
#include "../include/optmanager.h"

int flagStatus(unsigned char option, unsigned char flags){
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