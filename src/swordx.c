
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <getopt.h>

#include "../include/optmanager.h"

int main(int argc, char **argv);
void usage();
void printHelp();

static struct option const long_opts[] =
        {
                {"help",             no_argument,       NULL, 'h'},
                {"recursive",        no_argument,       NULL, 'r'},
                {"follow",           no_argument,       NULL, 'f'},
                {"exclude",          required_argument, NULL, 'e'},
                {"alpha",            no_argument,       NULL, 'a'},
                {"min",              required_argument, NULL, 'm'},
                {"ignore",           required_argument, NULL, 'i'},
                {"sortbyoccurrency", no_argument,       NULL, 's'},
                {"sbo",              no_argument,       NULL, 's'},
                {"output",           required_argument, NULL, 'o'},
                {"log",              required_argument, NULL, 'l'},
                {"update",           required_argument, NULL, 'u'},
                {NULL, 0,                               NULL, 0} // required
        };

int main(int argc, char **argv) {
    int c;

//     Dentro ad ogni funzione attivo i flag
    while ((c = getopt_long(argc, argv, "hrfeamisolu", long_opts, NULL)) != -1) {
        switch (c) {
            case 'h':
                // do something
                break;
                
            case 'r':
                // do something
                break;

            case 'f':
                // do something
                break;
                
            case 'e':
                // do something
                break;

            case  'a':
                // do something
                break;
            
            case 'm':
                // do something
                break;

            case 'i':
                // do something
                break;

            case 's':
                // do something
                break;

            case 'o':
		// do something
            	break;

            case 'l':
                // do something
                break;

            case 'u':
                // do something
                break;
        }
    }

    if(!argv[1]){
        fprintf(stderr, "swordx: no input files or directory\n");
        usage();
        exit(EXIT_FAILURE);
    }

    Tree *albero = nodeAlloc();
    char *path = argv[1];

    albero = getWords(albero, path);
    printTree(albero);

    free(albero);
    return 0;
}

void usage(){
    printf("Usage: swordx [options] [inputs]\n");
}

void printHelp() {
    printf("Uso: swordx [options] [inputs]\n");
    printf("SWORDX: Stampo help qui\n");
}
