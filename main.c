/*
 * main2.c
 * 
 * Copyright 2018 Davide <davide@davide-pc>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "tree.h"

// Tree *albero = NULL;

// Prototipi di funzioni
/* Inserisco i prototipi di funzioni */

/*Tree *initializeTree(Tree *albero, char *value){
	albero = malloc(sizeof(Tree*));
	albero->value=value;
    return albero;
}*/

Tree *nodeAlloc(){ // SISTEMARE
	return (Tree*)malloc(sizeof(Tree*));
}

Tree *insertNode(Tree* albero, char *word){
	if(albero == NULL) {
		albero = nodeAlloc();
		strcpy(albero->value, word);
		albero->occurrences = 1;
		albero->left = NULL;
		albero->right = NULL;
	}else if (strcmp(word, albero->value)==0){
		albero->occurrences+=1;
	}else if (strcmp(word, albero->value)<0){
		albero->left=insertNode(albero->left, word);
	}else if (strcmp(word, albero->value)>0){
		albero->right = insertNode(albero->right, word);
	}
	return albero;
}

//FILE openFile(){ ... }  ritorna variabile di tipo FILE

Tree *getWords(Tree* albero, char *path){
    FILE *rFile;
    char *buffer, *word;
//    char *buffer;
//    char *word = malloc(sizeof(char *));
    size_t linesize = 0;
	
	rFile = fopen(path, "r");  // r -> apro il file in sola lettura (Read).
	
	// Stampo il contenuto del file
    if(rFile == NULL) fprintf(stderr,"SWORDX: Errore durante l'apertura del file");
    else {
        while (getline(&buffer, &linesize, rFile) > 0) {
            word = strtok(buffer, " ,.:;-_[]()/!£$%&?^|*€@#§°*'");
            while (word != NULL) {
				albero = insertNode(albero, word);
                word = strtok(NULL, " ,.:;-_[]()/!£$%&?^|*€@#§°*'");
            }
        }
    }
    fclose(rFile);
    return albero;
}

void printTree(Tree* albero) {
    if (albero != NULL) {
        printTree(albero->left);
        printf("%s: %i\n", albero->value, albero->occurrences);
        printTree(albero->right);
    }
}

int main(int argc, char **argv)
{
	Tree *albero;
	albero = NULL;
	char *path = "/home/davide/Scrivania/prova.txt";
	albero = getWords(albero, path);
	
	printTree(albero);

	/*int a = 0;
	a = strcmp("ciao", "ciao");
	printf("%i", a);*/

    return 0;
}

