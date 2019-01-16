
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <getopt.h>

#include "../include/test.h"

static struct option const long_opts[];
int main(int argc, char **argv);
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
    Stack *listFiles = initializeNode();
    unsigned char flags = 0;  // HEX


//     Dentro ad ogni funzione attivo i flag
    while ((c = getopt_long(argc, argv, "hrfeamisolu", long_opts, NULL)) != -1) {
        switch (c) {
            case 'h':
                printHelp();
                break;

            case 'o':
                optind--;
                for (; optind < argc && *argv[optind] != '-'; optind++) {
                    printf("o: %s \n", argv[optind]);
                }
//                printf("o: %s \n", optarg);

                break;

            case 'e':
                test_stack();
                break;

            case 'm':
                test_albero();
                break;

            case 'r':
                test_flags();
                break;

            default:
                fprintf(stderr, "prova"); // da sistemare il messaggio d'errore
                break;
        }
    }

    return 0;
}

void printHelp() {
    printf("Uso: swordx [options] [inputs]\n");
    printf("SWORDX: Stampo help qui\n");
}
